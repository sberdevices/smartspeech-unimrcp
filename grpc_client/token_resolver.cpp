#include "token_resolver.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

#ifdef __cplusplus
extern "C" {
#endif
#include <apr_uuid.h>
#ifdef __cplusplus
}
#endif

namespace smartspeech {

void token_resolver::global_init() {
  static bool f = false;
  if (!f) {
    f = true;
    curl_global_init(CURL_GLOBAL_NOTHING);
  }
}

void token_resolver::global_cleanup() {
  static bool f = false;
  if (!f) {
    f = true;
    curl_global_cleanup();
  }
}

token_resolver::token_resolver(const std::string &sm_url, const std::string &client_id, const std::string &secret)
    : url_(sm_url)
    , client_id_(client_id)
    , secret_(secret)
    , curl_(nullptr) {
  apr_uuid_t apr_uuid;
  apr_uuid_get(&apr_uuid);
  std::string uuid_str;
  uuid_str.resize(APR_UUID_FORMATTED_LENGTH + 1);
  apr_uuid_format(uuid_str.data(), &apr_uuid);

  uuid_.assign(uuid_str);
}

token_resolver::~token_resolver() {}

static size_t on_received(void *received_data, size_t size, size_t count, void *userdata) {
  size_t realsize = size * count;

  if (realsize) {
    auto *secret = static_cast<std::string *>(userdata);
    secret->append(static_cast<char *>(received_data), realsize);
  }

  return realsize;
}

std::string token_resolver::get_token() {
  curl_ = curl_easy_init();

  std::string token{};

  curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, on_received);
  curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &token);

  struct curl_slist *hs = NULL;
  hs = curl_slist_append(hs, "Content-Type: application/x-www-form-urlencoded");
  std::string rquid = std::string{"RqUID: "} + uuid_;
  hs = curl_slist_append(hs, rquid.c_str());

  curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, hs);

  curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl_, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
  curl_easy_setopt(curl_, CURLOPT_USERNAME, client_id_.c_str());
  curl_easy_setopt(curl_, CURLOPT_PASSWORD, secret_.c_str());

  curl_easy_setopt(curl_, CURLOPT_POST, 1L);
  curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, "scope=SMART_SPEECH");

  std::string secret_url = url_ + "/api/v2/oauth";
  curl_easy_setopt(curl_, CURLOPT_URL, secret_url.c_str());

  CURLcode res = curl_easy_perform(curl_);
  if (res == CURLE_OK && !token.empty()) {
    auto json = nlohmann::json::parse(token);
    if (json.count("access_token")) {
      token_ = json["access_token"];
    }
  }
  curl_slist_free_all(hs);
  curl_easy_cleanup(curl_);

  return token_;
}
}  // namespace smartspeech