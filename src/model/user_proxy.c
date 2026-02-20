#include "user_proxy.h"

#include <string.h>

static size_t count(const struct UserProxy *self) {
    const struct IProxy *this = self->super;
    const struct UserVO *users = this->getData(this);

    size_t total = 0;
    for (size_t i = 0; i < MAX_USERS; i++) {
        if (users[i].username == NULL || users[i].username[0] == '\0')
            break;
        total++;
    }
    return total;
}

static bool indexOf(const struct UserProxy *self, const char *username, size_t *out) {
    const struct IProxy *this = self->super;
    const struct UserVO *users = this->getData(this);

    const size_t count = self->count(self);
    for (size_t i = 0; i < count; i++) {
        if (strcmp(users[i].username, username) == 0) { // match
            if (out) *out = i;
            return true;
        }
    }
    return false;
}

static size_t list(const struct UserProxy *self, struct UserVO **out, const size_t max) {
    const struct IProxy *this = self->super;
    struct UserVO *users = this->getData(this);

    const size_t count = self->count(self);
    const size_t total = count < max ? count : max; // max = caller buffer capacity
    for (size_t i = 0; i < total; i++) {
        out[i] = &users[i];
    }
    return total;
}

static bool add(const struct UserProxy *self, const struct UserVO *user) {
    const struct IProxy *this = self->super;
    struct UserVO *users = this->getData(this);

    const size_t count = self->count(self);
    if (count >= MAX_USERS) return false; // overflow

    size_t index = 0;
    if (self->indexOf(self, user->username, &index) == true) // existing
        return false;

    users[count] = *user;

    return true;
}

static bool update(const struct UserProxy *self, const struct UserVO *user) {
    const struct IProxy *this = self->super;
    struct UserVO *users = this->getData(this);

    size_t index;
    if (self->indexOf(self, user->username, &index) == false) // find
        return false; // mismatch

    users[index] = *user;
    return true;
}

static bool delete(const struct UserProxy *self, const struct UserVO *user, struct UserVO *out) {
    const struct IProxy *this = self->super;
    struct UserVO *users = this->getData(this);

    size_t index;
    if (self->indexOf(self, user->username, &index) == false) // find
        return false; // mismatch

    if (out != NULL) *out = users[index];

    const size_t count = self->count(self);
    for (size_t i = index; i < count - 1; i++) { // shift left
        users[i] = users[i + 1];
    }
    users[count - 1] = (struct UserVO){0};

    return true;
}

struct IProxy *user_proxy_init(void *buffer, const char *name, void *data) {
    struct IProxy *proxy = puremvc_proxy_init(buffer, name, data);
    return proxy;
}

struct UserProxy *user_proxy_bind(struct UserProxy *proxy, struct IProxy *super) {
    proxy->super = super;

    proxy->count = count;
    proxy->indexOf = indexOf;
    proxy->list = list;
    proxy->add = add;
    proxy->update = update;
    proxy->delete = delete;

    return proxy;
}
