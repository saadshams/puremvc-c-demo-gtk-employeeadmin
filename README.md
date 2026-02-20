

#define NAME_MAX 31
#define EMAIL_MAX 63
#define PHONE_MAX 15
#define ADDRESS_MAX 64

typedef struct {
char first[NAME_MAX + 1];  /**< First name, max 31 chars + null */
char last[NAME_MAX + 1];   /**< Last name, max 31 chars + null */
char email[EMAIL_MAX + 1]; /**< Email, max 63 chars + null */
char phone[PHONE_MAX + 1]; /**< Phone number, max 15 chars + null */
char street[ADDRESS_MAX + 1];
char city[NAME_MAX + 1];
char state[16 + 1];
char zip[10 + 1];
char country[NAME_MAX + 1];
} Person;
