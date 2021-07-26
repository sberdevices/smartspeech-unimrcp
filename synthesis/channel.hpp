#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <apt_consumer_task.h>
#include <mpf_stream.h>
#include <mrcp_engine_types.h>
#include <mrcp_message.h>


#ifdef __cplusplus
}
#endif

#include <memory>
#include <vector>
#include <mutex>
#include <grpc_client/client.hpp>

namespace smartspeech::mrcp::synthesis {
class channel {
 public:
  struct params {
	mrcp_engine_t *mrcp_engine;
	apr_pool_t *pool;
	apt_consumer_task_t *event_loop;
	std::shared_ptr<smartspeech::grpc::client> smartspeech_grpc_client;
  };

 public:
  explicit channel(const params &params);
  ~channel();

  mrcp_engine_channel_t *mrcp_channel() const;

  void feel_voice_buffer(void *buffer, size_t length);
  apt_bool_t on_open();
  apt_bool_t on_close();
  apt_bool_t on_message(mrcp_message_t *request);
  void on_voice(const smartspeech::grpc::synthesis::result &result);

 private:
  void send_mrcp_response(mrcp_message_t *response);
  void send_result_event();
  void update_mrcp_params(mrcp_message_t *request);
  void start_synthesis(const std::string &text);
  void shedule_stop_synthesis();
  void stop_synthesis();

  void process_set_params(mrcp_message_t *request);
  void process_synthesis(mrcp_message_t *request);
  void process_stop(mrcp_message_t *request);

 private:
  apr_pool_t *pool_;
  apt_consumer_task_t *event_loop_;
  mrcp_engine_channel_t *mrcp_channel_;

  std::shared_ptr<smartspeech::grpc::client> smartspeech_grpc_client_;
  smartspeech::grpc::synthesis::connection* smartspeech_grpc_synthesis_connection_;

  enum class state {
	idle, synthesis
  } state_;

  struct mrcp_params {
    std::string voice_name;
  };
  mrcp_params mrcp_params_;

  /* active requests */
  mrcp_message_t *synthesis_request_;

  std::mutex voice_buffer_m_;
  std::vector<uint8_t> voice_buffer_;
};
}