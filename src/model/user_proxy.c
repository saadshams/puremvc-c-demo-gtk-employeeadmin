#include "user_proxy.h"

struct IProxy *user_proxy_init(void *buffer, const char *name, void *data) {
    struct IProxy *proxy = puremvc_proxy_init(buffer, name, data);
    return proxy;
}
