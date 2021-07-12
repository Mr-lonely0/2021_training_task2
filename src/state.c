#include "state.h"

void init_State(struct State *s) {
    // TODO
    s = (struct State *)malloc(sizeof(struct State));
    s->index = 0;
    s->r = s->g = s->b = -1;
    s->industry = -1;
    s->next = -1;
}
void delete_State(struct State *s) {
    // TODO
    free(s);
}
void parse(struct State *s, struct PNG *p) {
    // TODO
    char file_name[] = "test1.png";
    
}
int solve1(struct State *s) {
    // TODO
    return 0;
}
int solve2(struct State *s) {
    // TODO
    return 0;
}
