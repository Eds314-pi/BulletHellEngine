#include "../include/runMethods.h"
#include "../include/readFile.h"
void updateAttack(struct fight *fight, struct bullet *bullets, struct beam *beams, struct spawner *spawners)
{
    for(int j = 0; j < MAX_BULLETS; j++)
        {
            
            if(fight->attacks[fight->currentAttack].moveset.bulletTimer[j] >= 0)
            {
                if(fight->attacks[fight->currentAttack].moveset.bulletTimer[j]>0)
                {
                    fight->attacks[fight->currentAttack].moveset.bulletTimer[j]--;
                }else{
                    fight->attacks[fight->currentAttack].moveset.bulletTimer[j]--;
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

        for(int i=0; i<MAX_BEAMS;i++)
        {
            if(fight->attacks[fight->currentAttack].moveset.beamTimer[i]>=0)
            {
                if(fight->attacks[fight->currentAttack].moveset.beamTimer[i]>0)
                {
                    fight->attacks[fight->currentAttack].moveset.beamTimer[i]--;
                }else{
                    for(int j=0;j<MAX_BEAMS;j++)
                    {
                        if(beams[j].lifetime==0 && fight->attacks[fight->currentAttack].moveset.beams[i].texture.id!=0)
                        {
                            beams[j]=fight->attacks[fight->currentAttack].moveset.beams[i];
                            fight->attacks[fight->currentAttack].moveset.beamTimer[i]=-1;
                            fight->attacks[fight->currentAttack].moveset.beams[i]=(struct beam){0};
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


        for(int i=0;i<MAX_SPAWNERS;i++)
        {
            if(fight->attacks[fight->currentAttack].moveset.spawnTimer[i]>=0)
            {
                if(fight->attacks[fight->currentAttack].moveset.spawnTimer[i]>0)
                {
                    fight->attacks[fight->currentAttack].moveset.spawnTimer[i]--;
                }else{
                    for(int j=0;j<MAX_SPAWNERS;j++)
                    {
                        if(spawners[j].lifetime==0 && fight->attacks[fight->currentAttack].moveset.spawners[i].texture.id!=0)
                        {
                            spawners[j]=fight->attacks[fight->currentAttack].moveset.spawners[i];
                            fight->attacks[fight->currentAttack].moveset.spawnTimer[i]=-1;
                            fight->attacks[fight->currentAttack].moveset.spawners[i]=(struct spawner){0};
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
}