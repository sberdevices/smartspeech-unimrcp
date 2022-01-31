#include "token_resolver.hpp"

#include <iostream>
#include <random>
#include <nlohmann/json.hpp>

namespace {
std::string get_uuid() {
  static std::random_device dev;
  static std::mt19937 rng(dev());

  std::uniform_int_distribution<int> dist(0, 15);

  const char *v = "0123456789abcdef";
  const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

  std::string res;
  for (int i = 0; i < 16; i++) {
      if (dash[i]) res += "-";
      res += v[dist(rng)];
      res += v[dist(rng)];
  }
  return res;
}
}

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
    , curl_(nullptr)
    , uuid_(get_uuid())
{}

token_resolver::~token_resolver() {}

static size_t on_received(void *received_data, size_t size, size_t count, void *userdata) {
  size_t realsize = size * count;

  if (realsize) {
    auto *secret = static_cast<std::string *>(userdata);
    secret->append(static_cast<char *>(received_data), realsize);
  }

  return realsize;
}

std::string token_resolver::get_token(const std::string &scope) {
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
  std::string scope_opt = std::string{"scope="} + scope;
  curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, scope_opt.c_str());
  curl_easy_setopt(curl_, CURLOPT_TIMEOUT, 3L);

  std::string secret_url = url_ + "/api/v2/oauth";
  curl_easy_setopt(curl_, CURLOPT_URL, secret_url.c_str());

  CURLcode res = curl_easy_perform(curl_);
  if (res == CURLE_OK && !token.empty()) {
    auto json = nlohmann::json::parse(token);
    if (json.count("access_token")) {
      token_ = json["access_token"];
    } else {
      std::cerr << "smartspecch: get token err: can't find token in the SmartMarket API response\n";
    }
  } else {
    std::cerr << "smartspeech: get token err: " << curl_easy_strerror(res) << std::endl;
  }
  curl_slist_free_all(hs);
  curl_easy_cleanup(curl_);

  return token_;
}
}  // namespace smartspeech
