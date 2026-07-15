#include "../include/runMethods.h"
#include "../include/readFile.h"
void updateAttack(struct fight *fight, struct bullet *bullets)
{
    for(int j = 0; j < MAX_BULLETS; j++)
        {
            
            if(fight->attacks[fight->currentAttack].moveset.bulletTimer[j] > 0)
            {
                fight->attacks[fight->currentAttack].moveset.bulletTimer[j]--;
            }
            if(fight->attacks[fight->currentAttack].moveset.bulletTimer[j] == 0)
            {
                for(int k = 0; k < MAX_BULLETS; k++)
                {
                    if(bullets[k].lifetime == 0 && fight->attacks[fight->currentAttack].moveset.bullets[j].texture.id!=0)
                    {
                        bullets[k] = fight->attacks[fight->currentAttack].moveset.bullets[j];
                        fight->attacks[fight->currentAttack].moveset.bulletTimer[j] = -1;
                        fight->attacks[fight->currentAttack].moveset.bullets[j]=(struct bullet){0};
                        fight->attacks[fight->currentAttack].moveset.total--;
                        if(fight->attacks[fight->currentAttack].moveset.total==0)
                        {
                           
                            fight->currentAttack++;
                        }

                        break;
                    }
                }
            }
        }
}