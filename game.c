#include "game.h"

#define MAXN  200

#define LENGTH 1
#define BLACK  0

struct Firework {
	int x, y;
	float vx, vy;
	int color;
	int mark;
	int timestamp;
	struct Firework *prev, *next;
	
} pool[MAXN], *top, *active;

struct Plane {
	int x,y;
	int cond[200][320];
	int bomb;
}plane;

struct Enemy{
	int x,y;
	int cond[200][320];
	int remember;
	struct Firework ptr1[3];
}buffer[4],boss;



int move_up,move_down,move_forward,move_back,shoot;
int flag=5;
int boss_up=0;

inline int
rand() {
	static int seed = 0;
	seed = 0x015A4E35 * seed + 1;
	return (seed >> 16) & 0x7FFF;
}

void
init_game(void) {
	int i,z;
	plane.x=80;
	plane.y=0;
	
	for (i = 0; i < MAXN - 1; i ++) {
		pool[i].next = pool + (i + 1);
	}
	
	int x=plane.x;
	int y=plane.y;
	plane.bomb=4;
	for(i=0;i<1935;i++){
		draw_pixel(x,y,array[i]);
		plane.cond[x][y]=array[i];
		y++;
		if(y>=0x2D){
			y=0;
			x++;
		}
	}
	
	y=280;
	for(z=0;z<4;z++){
		buffer[z].y=y;
	}
	
	buffer[0].x=0;
	buffer[1].x=45;
	buffer[2].x=90;
	buffer[3].x=140;
			
	int temp,j;
	for(z=0;z<4;z++){
		temp=buffer[z].x;
		j=buffer[z].y;
		for(i=0;i<1804;i++){
			draw_pixel(temp,j,enemy[i]);
			buffer[z].cond[temp][j]=enemy[i];
			j++;
			if((j-buffer[z].y)>=44){
				j=buffer[z].y;
				temp++;
			}
		}
		buffer[z].ptr1[0].mark=0;
		buffer[z].remember=10;
	}
	boss.remember=0;
	for(i=0;i<3;i++){
		boss.ptr1[i].mark=0;
	}
	pool[MAXN - 1].next = NULL;
	
	top = pool;
	active = NULL;
}


void
start_frame(void) {
	struct Firework *ptr;
	int i;	
	static int count=0;
	int x,y,dire,z;
		

	if((count+1)%11==0&&plane.bomb>0&&flag>=0){
		if(move_up==1){		//up
			x=plane.x;
			y=plane.y;
		
			for(i=0;i<1935;i++){
				if(plane.cond[x][y]!=0){
					draw_pixel(x,y,0);
					plane.cond[x][y]=0;
				}
				y++;
				if(y>=(plane.y+45)){
					y=plane.y;
					x++;
				}
			}
			if(plane.x<=5) plane.x=0;
			else plane.x=plane.x-5;
			x=plane.x;
			y=plane.y;
			for(i=0;i<1935;i++){
				plane.cond[x][y]=array[i];
				if(array[i]!=0){
					draw_pixel(x,y,array[i]);
				}
				y++;
				if(y>=(plane.y+45)){
					y=plane.y;
					x++;
				}
			}
		}
		if(move_down==1){		//down
			x=plane.x;
			y=plane.y;
		
			for(i=0;i<1935;i++){
				if(plane.cond[x][y]!=0){
					draw_pixel(x,y,0);
					plane.cond[x][y]=0;
				}
				y++;
				if(y>=(plane.y+45)){
					y=plane.y;
					x++;
				}
			}
			if(plane.x>=152) plane.x=157;
			else plane.x=plane.x+5;;
			x=plane.x;
			y=plane.y;
			for(i=0;i<1935;i++){
				plane.cond[x][y]=array[i];
				if(array[i]!=0){
					draw_pixel(x,y,array[i]);
				}
				y++;
				if(y>=(plane.y+45)){
					y=plane.y;
					x++;
				}
			}
		}
		if(move_forward==1){		//forward
			x=plane.x;
			y=plane.y;
		
			for(i=0;i<1935;i++){
				if(plane.cond[x][y]!=0){
					draw_pixel(x,y,0);
					plane.cond[x][y]=0;
				}
				y++;
				if(y>=(plane.y+45)){
					y=plane.y;
					x++;
				}
			}
			if(plane.y>=270) plane.y=275;
			else plane.y=plane.y+5;
			x=plane.x;
			y=plane.y;
			for(i=0;i<1935;i++){
				plane.cond[x][y]=array[i];
				if(array[i]!=0){
					draw_pixel(x,y,array[i]);
				}
				y++;
				if(y>=(plane.y+45)){
					y=plane.y;
					x++;
				}
			}
		}
		if(move_back==1){		//back
			x=plane.x;
			y=plane.y;
		
			for(i=0;i<1935;i++){
				if(plane.cond[x][y]!=0){
					draw_pixel(x,y,0);
					plane.cond[x][y]=0;
				}
				y++;
				if(y>=plane.y+45){
					y=plane.y;
					x++;
				}
			}
			if(plane.y<=5)plane.y=0;
			else plane.y=plane.y-5;
			x=plane.x;
			y=plane.y;
			for(i=0;i<1935;i++){
				plane.cond[x][y]=array[i];
				if(array[i]!=0){
					draw_pixel(x,y,array[i]);
				}
				y++;
				if(y>=(plane.y+45)){
					y=plane.y;
					x++;
				}
			}
		}
		if(shoot==1){			//shoot
			
			int bufferx[]={plane.x+42,plane.x+21,plane.x};
			int buffery[]={plane.y+20,plane.y+46,plane.y+20};
		
			for(i=0;i<3;i++){
				if (top == NULL){
					return;
				}
				
				ptr = top;
				top = top->next;
			
				ptr->x = bufferx[i];
				ptr->y = buffery[i];
				ptr->vx = 0;
				ptr->vy = 1;
				ptr->color = 100;
				ptr->mark=0;
				ptr->timestamp = 0;
				ptr->next = active;
				ptr->prev = NULL;
				if (active != NULL) active->prev = ptr;
				active = ptr;
				
			}
		}
	}
	count++;
	if((count+1)%20==0&&plane.bomb>0){
		for(z=0;z<4;z++){
			if(buffer[z].remember>0){
				y=buffer[z].y;
				x=buffer[z].x;
				for(i=0;i<1804;i++){
					if(buffer[z].cond[x][y]!=0){
						draw_pixel(x,y,0);
						buffer[z].cond[x][y]=0;
					}
					y++;
			
					if((y-buffer[z].y)>=44){
						y=buffer[z].y;
						x++;
					}
				}
				
				dire=rand()%3;
				switch(dire){
					case 0:{ 
						if(buffer[z].x<=2) buffer[z].x=0;	else buffer[z].x=buffer[z].x-2;
						};break;
					case 1: {
						if(buffer[z].x>=180) buffer[z].x=180;	else buffer[z].x=buffer[z].x+2;
						};break;
					case 2: buffer[z].y=buffer[z].y-2;break;
				}
				buffer[z].y=buffer[z].y-1;
				y=buffer[z].y;
				
				x=buffer[z].x;
				for(i=0;i<1804;i++){
					buffer[z].cond[x][y]=enemy[i];
					if(enemy[i]!=0){
						draw_pixel(x,y,enemy[i]);
					}
					y++;
					
					if((y-buffer[z].y)>=44){
						y=buffer[z].y;
						x++;
					}
				}
			}
		}	
	}
	if(plane.bomb>0){
		for(z=3;z>=0;z--){					//enemy shoot
			if(buffer[z].ptr1[0].mark==0&&buffer[z].remember>0){
				buffer[z].ptr1[0].x = buffer[z].x+21;
				buffer[z].ptr1[0].y = buffer[z].y;
			
				buffer[z].ptr1[0].color = 15;
			
				buffer[z].ptr1[0].timestamp = 0;
				buffer[z].ptr1[0].mark=1;
			}
		}
	}
	
	for(z=0;z<4;z++){
		
		draw_pixel(buffer[z].ptr1[0].x,buffer[z].ptr1[0].y,BLACK );
		buffer[z].ptr1[0].y=buffer[z].ptr1[0].y-1;
	}

	
	for(z=0;z<4;z++){
		
		if(buffer[z].ptr1[0].y<=0)
			buffer[z].ptr1[0].mark=0;
		else{	if(buffer[z].ptr1[0].mark==1){
				draw_pixel(buffer[z].ptr1[0].x,buffer[z].ptr1[0].y,buffer[z].ptr1[0].color);	
				if(plane.cond[buffer[z].ptr1[0].x][buffer[z].ptr1[0].y-1]!=0){
					buffer[z].ptr1[0].mark=0;
					plane.bomb--;
					draw_pixel(buffer[z].ptr1[0].x,buffer[z].ptr1[0].y,BLACK);
					if(plane.bomb<=0){
						x=plane.x;
						y=plane.y;
						
						for(i=0;i<1935;i++){
							if(plane.cond[x][y]!=0){
								draw_pixel(x,y,0);
								plane.cond[x][y]=0;
							}
							y++;
							if(y>=plane.y+45){
								y=plane.y;
								x++;
							}
						}
					}
				}
			}
		}
	}
	
	if(flag==1){		//create boss
		flag--;
		boss.x=20;
		boss.y=220;
		x=boss.x;
		y=boss.y;
		boss.remember=1000;
		for(i=0;i<10509;i++){
			boss.cond[x][y]=Jyy[i];
			if(Jyy[i]!=0){
				draw_pixel(x,y,Jyy[i]);
			}
			y++;
			if(y>=boss.y+93){
				y=boss.y;
				x++;
			}
		}
	}
	if(count%20==0&&boss.remember>0&&plane.bomb>0){		//boss can move up or move down
		y=boss.y;
		x=boss.x;
		for(i=0;i<10509;i++){
			if(boss.cond[x][y]!=0){
				draw_pixel(x,y,0);
				boss.cond[x][y]=0;
			}
			y++;
	
			if((y-boss.y)>=93){
				y=boss.y;
				x++;
			}
		}
		if(boss_up==0){
			if(boss.x<=85)
				boss.x=boss.x+1;
			else{
				boss.x=86;
				boss_up=1;
			}
		}
		else{
			if(boss.x>=1)
				boss.x=boss.x-1;
			else{
				boss.x=0;
				boss_up=0;
			}
		}
		x=boss.x;
		y=boss.y;
		for(i=0;i<10509;i++){
			boss.cond[x][y]=Jyy[i];
			if(Jyy[i]!=0){
				draw_pixel(x,y,Jyy[i]);
			}
			y++;
			if(y>=boss.y+93){
				y=boss.y;
				x++;
			}
		}
		
	}
	
	if(flag==0&&plane.bomb>0){
		x=boss.x;
		y=boss.y;
		int bufferx[]={x+4,x+55,x+108};
		int buffery[]={y+50,y,y+50};
		for(i=0;i<3;i++){
			if(boss.ptr1[i].mark==0){
				boss.ptr1[i].x=bufferx[i];
				boss.ptr1[i].y=buffery[i];
				boss.ptr1[i].color = 15;
			
				boss.ptr1[i].timestamp = 0;
				boss.ptr1[i].mark=1;
			}
		}
	}
	for(i=0;i<3;i++){
		draw_pixel(boss.ptr1[i].x,boss.ptr1[i].y,BLACK);
		boss.ptr1[i].y=boss.ptr1[i].y-1;
	}
	
	for(i=0;i<3;i++){
		if(boss.ptr1[i].y<=0)
			boss.ptr1[i].mark=0;
		else{
			if(boss.ptr1[i].mark==1){
				draw_pixel(boss.ptr1[i].x,boss.ptr1[i].y,boss.ptr1[i].color);	
				if(plane.cond[boss.ptr1[i].x][boss.ptr1[i].y-1]!=0){
					boss.ptr1[i].mark=0;
					plane.bomb--;
					draw_pixel(boss.ptr1[i].x,boss.ptr1[i].y,BLACK);
					if(plane.bomb<=0){
						x=plane.x;
						y=plane.y;
						
						for(i=0;i<1935;i++){
							if(plane.cond[x][y]!=0){
								draw_pixel(x,y,0);
								plane.cond[x][y]=0;
							}
							y++;
							if(y>=plane.y+45){
								y=plane.y;
								x++;
							}
						}
					}
				}
			}
		}
	}
	
	if(flag==-1){
		x=0,y=0;
		for(i=0;i<64000;i++){
			draw_pixel(x,y,NB[i]);
			y++;
			if(y>=320){
				y=0;
				x++;
			}
		}
	}
	if(plane.bomb<=0){
		x=0,y=0;
		for(i=0;i<64000;i++){
			draw_pixel(x,y,SB[i]);
			y++;
			if(y>=320){
				y=0;
				x++;
			}
		}
	}
	/* .erase the trace */
	for (ptr = active; ptr != NULL; ptr = ptr->next) {
		draw_pixel( ptr->x, ptr->y+ptr->timestamp, BLACK );	
	}
	
	ptr = active;
	
	while (ptr != NULL) {
		struct Firework *prev=ptr->prev, *next = ptr->next;
		ptr->timestamp ++;
		
		if (ptr->timestamp > 320) {	//have some problem,it should have a circle.
			if (prev != NULL) prev->next = next;
			if (next != NULL) next->prev = prev;

			if (prev == NULL && next == NULL) active = NULL;
			ptr->next = top;
			ptr->prev = NULL;
			top = ptr;
		} else {	
				if(ptr->mark==0){
					
					draw_pixel( ptr->x, ptr->y+ptr->timestamp, ptr->color );
					int j;
					if(flag==0){		//judge whether the boss appear
						if(boss.cond[ptr->x][ptr->y+ptr->timestamp+2]!=0){	
							ptr->mark=1;
							boss.remember--;
							if(boss.remember<=0){
								flag--;
								x=boss.x,y=boss.y;
								for(j=0;j<10509;j++){
									draw_pixel(x,y,0);
									boss.cond[x][y]=0;
									y++;
									if(y>=boss.y+93){
										y=boss.y;
										x++;
									}
								}
							}
						}
					}
					for(z=0;z<4;z++){
						if(buffer[z].cond[ptr->x][ptr->y+ptr->timestamp+2]!=0){
							ptr->mark=1;
							buffer[z].remember--;
							if(buffer[z].remember<=0){
								flag--;
								int newy=buffer[z].y,newx=buffer[z].x;
								for(j=0;j<1804;j++){
									draw_pixel(newx,newy,0);
	
									buffer[z].cond[newx][newy]=0;
									newy++;
									if((newy-buffer[z].y)>=44){
										newy=buffer[z].y;
										newx++;
									}
								}
							}
							
						}
					}
					
				}
			}
		ptr = next;
	}
	
}


void
key_stroke(int code) {
	if(code==72)		//up
		move_up=1;
	if(code==72+128)	//up
		move_up=0;
	if(code==80)		//down
		move_down=1;
	if(code==80+128)	//down
		move_down=0;
	if(code==77)		//forward
		move_forward=1;
	if(code==77+128)	//forward
		move_forward=0;
	if(code==75)		//back
		move_back=1;
	if(code==75+128)	//back
		move_back=0;
	if(code==57)		//shoot
		shoot=1;
	if(code==57+128)	//shoot
		shoot=0;
		
}







