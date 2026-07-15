#include "../include/runMethods.h"
//Decay activates whenever decay timer is the only frames left is slowly dissapate beam 
void growthDecay(struct beam*beams, Sound hurty, Sound beam, Vector2 beamCollison[4],bool* immunity, int* health);
void updateBeams(struct beam beams[], Sound hurty, Sound beam, Vector2 beamCollison[4], bool* immunty, int* health)
{
    for(int i=0;i<MAX_BEAMS;i++)
    {
        if(beams[i].lifetime!=0)
        {
            beams[i].collison[0]=(Vector2){beams[i].hurtbox.x,beams[i].hurtbox.y};
            beams[i].collison[1]=(Vector2){beams[i].hurtbox.x+beams[i].hurtbox.width,beams[i].hurtbox.y};
            beams[i].collison[2]=(Vector2){beams[i].hurtbox.x+beams[i].hurtbox.width,beams[i].hurtbox.y+beams[i].hurtbox.height};
            beams[i].collison[3]=(Vector2){beams[i].hurtbox.x,beams[i].hurtbox.y+beams[i].hurtbox.height};
            
            //finds vector corners for collison
            float a = beams[i].angle * DEG2RAD;
            for (int j = 0; j < 4; j++)
            {
                float x = beams[i].collison[j].x - beams[i].hurtbox.x;
                float y = beams[i].collison[j].y - beams[i].hurtbox.y;
                beams[i].collison[j].x = beams[i].hurtbox.x + x * cos(a) - y * sin(a);
                beams[i].collison[j].y = beams[i].hurtbox.y + x * sin(a) + y * cos(a);
            }
            beams[i].lifetime--;
            growthDecay(&beams[i], hurty, beam, &beamCollison[4],immunty,health);
            beams[i].pos = (Vector2){0, beams[i].hurtbox.height / 2};
            if(beams[i].lifetime==0)
            {
                beams[i]=(struct beam){0};
            }
        }
    }
}

void DrawBeams(struct beam beams[], Sound hurty, Sound beam, Vector2 beamCollison[4], bool* immunty, int* health)
{
    for(int i=0;i<MAX_BEAMS;i++)
    {
        if(beams[i].lifetime!=0)
        {
            DrawTexturePro(beams[i].texture,beams[i].scource,beams[i].hurtbox,beams[i].pos,beams[i].angle,WHITE);
        }
    }
}

void growthDecay(struct beam*beams, Sound hurty, Sound beam, Vector2 beamCollison[4],bool* immunity, int* health)
{
    if(beams->lifetime==DECAY_TIMER)
    {
        beams->decay=true;
    }
    //ensures sound playes once
    if(!beams->fired)
    {
        PlaySound(beam);
        beams->fired=true;
    }
    if(beams->power<beams->maxPower && !beams->decay)
            {
                beams->power += (float)beams->maxPower / 30.0f;
                beams->hurtbox.height=beams->power;
            }else 
                //Only checks for collision assuming beam is at full power
                for(int j=0;j<4;j++)
                {
                    if(CheckCollisionPointPoly((Vector2){beamCollison[j].x,beamCollison[j].y},beams->collison,4) && !beams->decay)
                    {
                        if(!(*immunity))
                        {
                            *health-=beams->damage;
                            *immunity=true;
                            PlaySound(hurty);
                        }
                    }
                }

            if(beams->decay)
            {
                beams->power -= (float)beams->maxPower / 30.0f;
                beams->hurtbox.height=beams->power;
            }
}