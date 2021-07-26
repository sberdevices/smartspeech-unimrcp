#pragma once

#include <string>
#include <curl/curl.h>

namespace smartspeech {
class token_resolver {
 public:
  token_resolver(const std::string &sm_url, const std::string &client_id, const std::string &secret);
  ~token_resolver();

  std::string get_token();

  static void global_init();
  static void global_cleanup();

 private:
  std::string url_;

  std::string uuid_;
  std::string client_id_;

  std::string secret_;
  std::string token_;

  CURL *curl_;
};
}