#include <stdio.h>
int negatearr(int arr[2]){
	int i,out[2];
	for (i=0;i<2;++i){
		arr[i]=-arr[i];
	}
}

int copy(int a[2],int b[2]){
	int i;
	for (i=0;i<2;++i){
		a[i]=b[i];
	}
}
int add(int coord1[2],int coord2[2],int out[2]){
	int i;
	for (i=0;i<2;++i){
		out[i]=coord1[i]+coord2[i];
	}
}
int gtchr(int chrnum){
	/*get character from character number 
	player1:chr1
	player2:chr2
	 */
	if (chrnum==0) return ' ';
	if (chrnum==1) return 'X';
	if (chrnum==2) return 'O';
}

int othplay(int player){
		if (player==1) return 2;
		else if (player==2) return 1;
}
int render(int grid[3][3]){
	int i,j;
	printf("+---+\n");
	for (i=2;i>=0;--i){
		printf("|");
		for (j=0;j<3;++j){
			if (grid[j][i]==0) putchar(gtchr(0));
			if (grid[j][i]==1) putchar(gtchr(1));
			if (grid[j][i]==2) putchar(gtchr(2));
		}
		printf("|");
		printf("\n");
	}
	printf("+---+\n");
	printf("\n");
}

int modulopos(int pos[]){
	int i;
	for (i=0;i<2;++i){
		pos[i]=pos[i]%3;
	}
}

int raycount(int pos[2],int vec[2],int grid[3][3],int lpla){
	/*counts the number of element along direction vec from pos*/
	int i,out[2],irow,outbound,tpos[2];
	irow=0;

	tpos[0]=pos[0];
	tpos[1]=pos[1];

	/*printf("initpos %d,%d\n",tpos[0],tpos[1]);*/

	outbound=0;
	while (outbound==0){

		add(tpos,vec,out);
		copy(tpos,out);
		/*printf("checked %d,%d\n",tpos[0],tpos[1]);*/

		if (tpos[0]<0||tpos[0]>2 || tpos[1]<0||tpos[1]>2) outbound=1;
		else if (grid[tpos[0]][tpos[1]]==lpla) {++irow; /*printf("is of same type\n")*/;}
	}
	/*printf("irow %d\n",irow);*/
	return irow;
}
int winner(int grid[3][3],int lpla,int lpos[]){
	int vec[4][2];
	int vecnum;
	int win;

	int irow;
	int pos[2];
	int i;
	int out[2];
	int middle;
	int diag;

	vec[0][0]=1; vec[0][1]=0;
	vec[1][0]=0; vec[1][1]=1;
	vec[2][0]=1; vec[2][1]=1;
	vec[3][0]=1; vec[3][1]=-1;

	vecnum=1;
	win=0;

	diag=0;

	i=0;
	while (i<4&&win==0){
		irow=1;
		irow+=raycount(lpos,vec[i],grid,lpla);
		negatearr(vec[i]);
		irow+=raycount(lpos,vec[i],grid,lpla);

		if (irow==3) win=1;
		++i;
	}

	return win;
}

int getinput(){
	int a,noinput;
	noinput=1;
	while ( noinput==1 ){
		a=getchar();
		if (a=='1') {return 0; noinput=0;}
		if (a=='2') {return 1; noinput=0;}
		if (a=='3') {return 2; noinput=0;}
	}
	return 3; /*error condition*/
}

int main (){
	int i,j,x,y;
	int win,rowcount;
	int grid[3][3],lpos[2];
	int lpla,playing,turns; 

	for (i=0;i<3;++i){
		for (j=0;j<3;++j){
			grid[i][j]=0;
		}
	}

	render(grid);
	lpla=1;
	playing=1;
	turns=0;

	putchar(gtchr(lpla));
	printf("'s turn!\n");
	
	while (playing==1&&turns<9){
		lpos[0]=getinput();
		lpos[1]=getinput();

		grid[lpos[0]][lpos[1]]=lpla;
		render(grid);

		win=winner(grid,lpla,lpos);

		if (win == 1){
			if (lpla==1) printf("X wins\n");
			else if (lpla==2) printf("O wins\n");
			playing=0;
		} 
		else if (win == 0) {
			putchar(gtchr(othplay(lpla)));
			printf("'s turn!\n");
		}
		else {
			printf("error: unexpected win value");
		}
		lpla=othplay(lpla);
		turns+=1;
	}
}


