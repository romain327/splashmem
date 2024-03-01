#include "actions.h"

t_bomb bombs[MAX_PLAYERS*BOMB_COUNTER];
t_bomb fake_bomb;
char cmd[MAX_PLAYERS] = {'0', '0', '0', '0'};


void actions_init(int argc, char *argv[])
{
    int i = 0;
	while (i < MAX_PLAYERS)
    {
		printf("Player %d is linked to %s\n", i+1, argv[i+1]);
        link_player(players[i], argv[i+1]);
        i++;
    }
	fake_bomb.id_p = 0;
	fake_bomb.id_b = -1;
	fake_bomb.x = 0;
	fake_bomb.y = 0;
	fake_bomb.timer = 0;
    for (int i = 0; i < MAX_PLAYERS*BOMB_COUNTER; i++)
    {
        bombs[i] = fake_bomb;
	}
}

void actions_do(t_player *p_player, enum action act_id)
{
    switch (act_id)
    {
        case ACTION_STILL:
			p_player->credits -= 1;
			world_paint_spot(p_player->x, p_player->y, p_player->id);
            break;
        case ACTION_MOVE_L:
			if (p_player->x == 0)
			{
				p_player->x += MAP_SIZE;
			}
			else {
                p_player->x--;
            }
			p_player->credits -= 1;
			world_paint_spot(p_player->x, p_player->y, p_player->id);
            break;
        case ACTION_MOVE_R:
            if (p_player->x == MAP_SIZE - 1)
            {
                p_player->x = 0;
            }
            else {
                p_player->x++;
            }
			p_player->credits -= 1;
			world_paint_spot(p_player->x, p_player->y, p_player->id);
            break;
        case ACTION_MOVE_U:
			if (p_player->y == 0)
            {
            	p_player->y += MAP_SIZE;
			}
			else {
                p_player->y--;
            }
			p_player->credits -= 1;
			world_paint_spot(p_player->x, p_player->y, p_player->id);
            break;
        case ACTION_MOVE_D:
            if (p_player->y == MAP_SIZE - 1)
            {
                p_player->y = 0;
            }
            else {
                p_player->y++;
            }
			p_player->credits -= 1;
			world_paint_spot(p_player->x, p_player->y, p_player->id);
            break;
        case ACTION_DASH_L:
			p_player->credits -= 10;
			if (p_player->credits < 0)
			{
			p_player->credits += 9;
	        }
			else {
            	for (int i = 0; i < 8; i++)
            	{
                	if (p_player->x == 0)
                	{
                		p_player->x += MAP_SIZE;
					}
					else {
	                    p_player->x--;
					}
                	world_paint_spot(p_player->x, p_player->y, p_player->id);
            	}
			}
            break;
        case ACTION_DASH_R:
			p_player->credits -= 10;
			if (p_player->credits < 0)
			{
			p_player->credits += 9;
			}
			else {
            	for (int i = 0; i < 8; i++)
            	{
                	if (p_player->x == MAP_SIZE - 1)
                	{
                		p_player->x = 0;
					}
					else {
                        p_player->x++;
					}
                	world_paint_spot(p_player->x, p_player->y, p_player->id);
            	}
			}
            break;
        case ACTION_DASH_U:
			p_player->credits -= 10;
			if (p_player->credits < 0)
			{
			p_player->credits += 9;
			}
			else {
            	for (int i = 0; i < 8; i++)
            	{
					if (p_player->y == 0)
					{
						p_player->y += MAP_SIZE-1;
					}
					else {
                    	p_player->y--;
					}
                	world_paint_spot(p_player->x, p_player->y, p_player->id);
            	}
			}
            break;
        case ACTION_DASH_D:
			p_player->credits -= 10;
			if (p_player->credits < 0)
			{
			p_player->credits += 9;
			}
			else {
            	for (int i = 0; i < 8; i++)
            	{
                	if (p_player->y == MAP_SIZE - 1)
                	{
                		p_player->y = 0;
					}
					else {
                    	p_player->y++;
					}
                	world_paint_spot(p_player->x, p_player->y, p_player->id);
            	}
			}
            break;
        case ACTION_TELEPORT_R:
			p_player->credits -= 2;
			if(p_player->credits < 0)
			{
			    p_player->credits += 1;
	        }
			else {
            	for (int i = 0; i < 8; i++)
            	{
                    if (p_player->x == MAP_SIZE - 1)
                    {
                		p_player->x = 0;
					}
					else {
                    	p_player->x++;
	                }
            	}
                world_paint_spot(p_player->x, p_player->y, p_player->id);
			}
            break;
        case ACTION_TELEPORT_L:
            p_player->credits -= 2;
			if(p_player->credits < 0)
			{
			    p_player->credits += 1;
			            }
			else {
			    for (int i = 0; i < 8; i++)
                {
                    if (p_player->x == 0)
                    {
                    	p_player->x += MAP_SIZE - 1;
				    }
			        else {
                    	p_player->x--;
			    	}
				}
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
			}
            break;
        case ACTION_TELEPORT_U:
            p_player->credits -= 2;
			if(p_player->credits < 0)
			{
			    p_player->credits += 1;
	        }
			else {
            	for (int i = 0; i < 8; i++)
            	{
                    if (p_player->y == 0)
                    {
                    	p_player->y += MAP_SIZE - 1;
                    }
                    else {
                    	p_player->y--;
                	}
            	}
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
			}
            break;
        case ACTION_TELEPORT_D:
            p_player->credits -= 2;
			if(p_player->credits < 0)
			{
			    p_player->credits += 1;
	        }
			else {
            	for (int i = 0; i < 8; i++)
            	{
                    if (p_player->y == MAP_SIZE - 1)
                    {
                    	p_player->y = 0;
                    }
                    else {
                    	p_player->y++;
                	}
            	}
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
			}
            break;
        case ACTION_SPLASH:
			p_player->credits -= 8;
			if(p_player->credits < 0)
            {
                p_player->credits += 7;
            }
            else {
				uint32_t x = p_player->x;
				uint32_t y = p_player->y;
            	if (p_player->x == 0)
            	{
            		p_player->x += MAP_SIZE - 1;
				}
				else {
                	p_player->x--;
				}
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
				if (p_player->y == 0)
                {
                    p_player->y += MAP_SIZE - 1;
                }
                else {
                	p_player->y--;
                }
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
				if (p_player->x == MAP_SIZE - 1)
                {
                    p_player->x = 0;
                }
                else {
                	p_player->x++;
                }
				world_paint_spot(p_player->x, p_player->y, p_player->id);
				if (p_player->x == MAP_SIZE - 1)
                {
                    p_player->x = 0;
                }
                else {
                	p_player->x++;
                }
				world_paint_spot(p_player->x, p_player->y, p_player->id);
				if (p_player->y == MAP_SIZE - 1)
                {
                    p_player->y = 0;
                }
                else {
                	p_player->y++;
                }
				world_paint_spot(p_player->x, p_player->y, p_player->id);
				if (p_player->y == MAP_SIZE - 1)
                {
                    p_player->y = 0;
                }
                else {
                	p_player->y++;
                }
				world_paint_spot(p_player->x, p_player->y, p_player->id);
				if (p_player->x == 0)
                {
                    p_player->x += MAP_SIZE - 1;
                }
                else {
                	p_player->x--;
                }
				world_paint_spot(p_player->x, p_player->y, p_player->id);
				if (p_player->x == 0)
                {
                    p_player->x += MAP_SIZE - 1;
                }
                else {
                	p_player->x--;
                }
				world_paint_spot(p_player->x, p_player->y, p_player->id);
				p_player->x = x;
				p_player->y = y;
				world_paint_spot(p_player->x, p_player->y, p_player->id);
			}
            break;
        case ACTION_BOMB:
            p_player->credits -= 9;
            if(p_player->credits < 0)
            {
                p_player->credits += 8;
            }
            else {
                t_bomb bomb;
				if (p_player->last_bomb == BOMB_COUNTER || p_player->bomb_drop == 0) {
					p_player->bomb_drop = 1;
				    p_player->last_bomb = 0;
					bomb.id_b = (p_player->id - 1) * BOMB_COUNTER + p_player->last_bomb;
				}
				else {
                	bomb.id_b = (p_player->id - 1) * BOMB_COUNTER + p_player->last_bomb + 1;
                    p_player->last_bomb++;
				}
				bomb.id_p = p_player->id;
                bomb.x = p_player->x;
                bomb.y = p_player->y;
                bomb.timer = BOMB_COUNTER;
				bombs[bomb.id_b] = bomb;
			}
            break;
        default:
            break;
    }
}

void link_player(t_player *p_player, char *lib)
{
    void *handle = dlopen(lib, RTLD_LAZY);
    if (!handle)
    {
        printf("Erreur lors du chargement de la bibliothèque %s\n", lib);
	    exit(1);
    }

    p_player->get_action = dlsym(handle, "get_action");

    if (!p_player->get_action)
    {
        printf("Erreur lors de la récupération de la fonction get_action pour %s\n", lib);
        dlclose(handle);
        exit(1);
    }
}

void explode_bomb(t_bomb *bomb) {
	uint32_t px = players[bomb->id_p-1]->x;
	uint32_t py = players[bomb->id_p-1]->y;

	players[bomb->id_p-1]->x = bomb->x;
	players[bomb->id_p-1]->y = bomb->y;
	players[bomb->id_p-1]->credits += 8;
	actions_do(players[bomb->id_p-1], ACTION_SPLASH);
	players[bomb->id_p-1]->x = px;
	players[bomb->id_p-1]->y = py;
	bombs[bomb->id_b] = fake_bomb;
}