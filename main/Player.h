#ifndef E_PLAYER
#define E_PLAYER

int
init_playercontext(void);

void
cleanup_playercontext(void);

void
cleanup_playercontext_crash(void);

int
run_app(void);

#endif