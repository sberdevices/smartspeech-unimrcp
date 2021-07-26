#include <mrcp_recog_engine.h>
#include <synthesis//cimpl.h>

MRCP_PLUGIN_VERSION_DECLARE

/** Main function  */
/** Plugin global initialization */
MRCP_PLUGIN_DECLARE(mrcp_engine_t *) mrcp_plugin_create(apr_pool_t *pool) {
  mrcp_engine_t *engine = smartspeech_synthesis_engine_create(pool);
  return engine;
}