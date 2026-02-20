Prerequisites
brew install autoconf automake libtool autoconf-archive

https://www.gtk.org/

https://docs.gtk.org/gtk3/visual_index.html

Install GNOME Builder
brew install --cask gnome-builder
gnome-builder


curl -L https://github.com/saadshams/puremvc-c-multicore-framework/archive/refs/tags/1.0.0.tar.gz | sha512sum

The "X-Macro" Pattern (for Enums and Strings)

```c++
/* * 1. THE SOURCE OF TRUTH (The X-Macro)
 * Define your notifications here.
 * The 'X' is a placeholder for a macro we will define later.
 */
#define NOTIFICATION_LIST(X) \
X(STARTUP,      "startup_note")    \
X(USER_LOGIN,   "user_login_note") \
X(USER_LOGOUT,  "user_logout_note")\
X(DATA_SYNC,    "data_sync_note")

/* * 2. GENERATE THE ENUM
 * We define X to extract only the first argument.
 */
#define AS_ENUM(id, name) id,

typedef enum {
    NOTIFICATION_LIST(AS_ENUM)
    NOTIFICATION_COUNT // Useful for array sizing
} NotificationType;

#undef AS_ENUM

/* * 3. GENERATE THE STRING TABLE
 * We define X to extract only the second argument.
 */
#define AS_STRING(id, name) name,

static const char* NOTIFICATION_NAMES[] = {
    NOTIFICATION_LIST(AS_STRING)
};

#undef AS_STRING

/* * 4. HELPER FUNCTION
 * Convert the enum value to a printable string.
 */
const char* get_notification_name(NotificationType type) {
    if (type >= 0 && type < NOTIFICATION_COUNT) {
        return NOTIFICATION_NAMES[type];
    }
    return "UNKNOWN";
}

void example() {
    // We can use the Enum constants directly
    NotificationType current_note = USER_LOGIN;

    printf("--- PureMVC X-Macro Example ---\n");

    // Print a specific notification
    printf("Enum ID: %d, String Name: %s\n",
            current_note,
            get_notification_name(current_note));

    printf("\n--- Iterating all Notifications ---\n");

    // We can iterate through them easily because of NOTIFICATION_COUNT
    for (int i = 0; i < NOTIFICATION_COUNT; i++) {
        printf("Index [%d]: %s\n", i, get_notification_name(i));
    }
}
```