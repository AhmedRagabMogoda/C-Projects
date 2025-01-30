
typedef struct linkedlist{
int val;
struct linkedlist *next;
}node_t;

int is_stack_linkedlist_empty(void);
void push_stack(int data);
int pop_stack(void);
void display_stack_elements(void);
int top_element_stack(void);
int number_of_elements_stack(void);
