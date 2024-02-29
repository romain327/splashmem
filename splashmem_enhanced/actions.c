#include "actions.h"

void actions_init(int argc, char *argv[])
{
    int i = 0;
	while (i < MAX_PLAYERS)
    {
		printf("Player %d is linked to %s\n", i+1, argv[i+1]);
        link_player(players[i], argv[i+1]);
        i++;
    }
}

void actions_do(t_player *p_player, enum action act_id)
{
	printf("Player %d is doing action %d\n", p_player->id, act_id);
    switch (act_id)
    {
        case ACTION_STILL:
			p_player->credits -= 1;
			world_paint_spot(p_player->x, p_player->y, p_player->id);
            break;
        case ACTION_MOVE_L:
            p_player->x--;
            if (p_player->x < 0)
			{
				p_player->x += MAP_SIZE;
			}
			p_player->credits -= 1;
			world_paint_spot(p_player->x, p_player->y, p_player->id);
            break;
        case ACTION_MOVE_R:
            p_player->x++;
            p_player->x = p_player->x % MAP_SIZE;
			p_player->credits -= 1;
			world_paint_spot(p_player->x, p_player->y, p_player->id);
            break;
        case ACTION_MOVE_U:
            p_player->y--;
            if (p_player->y < 0)
            {
            	p_player->y += MAP_SIZE;
			}
			p_player->credits -= 1;
			world_paint_spot(p_player->x, p_player->y, p_player->id);
            break;
        case ACTION_MOVE_D:
            p_player->y++;
            p_player->y = p_player->y % MAP_SIZE;
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
                	p_player->x--;
                	if (p_player->x < 0)
                	{
                		p_player->x += MAP_SIZE;
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
                	p_player->x++;
                	p_player->x = p_player->x % MAP_SIZE;
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
                	p_player->y--;
                	if (p_player->y < 0)
					{
						p_player->y += MAP_SIZE;
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
                	p_player->y++;
                	p_player->y = p_player->y % MAP_SIZE;
                	world_paint_spot(p_player->x, p_player->y, p_player->id);
            	}
			}
            break;
        case ACTION_TELEPORT_L:
			p_player->credits -= 2;
			if(p_player->credits < 0)
			{
			    p_player->credits += 1;
	        }
			else {
            	p_player->x += 8;
            	p_player->x = p_player->x % MAP_SIZE;
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
			}
            break;
        case ACTION_TELEPORT_R:
            p_player->credits -= 2;
			if(p_player->credits < 0)
			{
			    p_player->credits += 1;
	        }
			else {
            	p_player->x -= 8;
            	if (p_player->x < 0)
				{
					p_player->x += MAP_SIZE;
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
            	p_player->y += 8;
            	p_player->y = p_player->y % MAP_SIZE;
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
            	p_player->y -= 8;
            	if (p_player->y < 0)
            	{
            		p_player->y += MAP_SIZE;
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
            	p_player->y -= 1;
            	if (p_player->y < 0)
            		{
            			p_player->y += MAP_SIZE;
					}
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
				p_player->x -= 1;
				if (p_player->x < 0)
				{
					p_player->x += MAP_SIZE;
				}
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
				p_player->y += 1;
				p_player->y = p_player->y % MAP_SIZE;
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
				p_player->y += 1;
				p_player->y = p_player->y % MAP_SIZE;
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
				p_player->x += 1;
				p_player->x = p_player->x % MAP_SIZE;
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
				p_player->x += 1;
				p_player->x = p_player->x % MAP_SIZE;
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
				p_player->y -= 1;
				if (p_player->y < 0)
				{
					p_player->y += MAP_SIZE;
				}
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
				p_player->y -= 1;
				if (p_player->y < 0)
				{
					p_player->y += MAP_SIZE;
				}
            	world_paint_spot(p_player->x, p_player->y, p_player->id);
				p_player->x = x;
				p_player->y = y;
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
                bomb.id_p = p_player->id;
                bomb.id_b = p_player->bomb_count + 1;
                bomb.color = p_player->color;
                bomb.x = p_player->x;
                bomb.y = p_player->y;
                bomb.timer = BOMB_COUNTER;
	            p_player->bomb_count++;
            }
			//TODO gestion des bombes
            break;
        default:
            break;
    }
}

void link_player(t_player *p_player, char *lib)
{
    void *handle = dlopen(lib, RTLD_NOW | RTLD_GLOBAL);
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