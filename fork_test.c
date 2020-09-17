#include <stdio.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_BUFFER 128

typedef struct msgbuf{
	long mtype;
	char mtext[MAX_BUFFER];
}msg;

int main(int argc, char* argv[]){
	int share_data = 1;
	int fork_flag = 0;
	key_t key;
	int msglen;
	int msgflag;
	key = 1234;
	int msgid;
	int status;

	fork_flag = fork();

	if(fork_flag >0){
		printf("I am parent\n");
		share_data++;
		printf("%d\n",share_data);

		msg snd_msg;
		msgflag = IPC_CREAT | 0666;
		msgid = msgget(key,msgflag);
		if(msgid < 0){
			perror("msgget");
			exit(1);
		}
	
		snd_msg.mtype = 1;
		strcpy(snd_msg.mtext,"fuck you");
		msglen = strlen(snd_msg.mtext) + 1;

		if(msgsnd(msgid,&snd_msg,msglen,IPC_NOWAIT) < 0){
			perror("msgsnd");
			exit(1);
		}
		else{
			printf("success to send / %s\n",snd_msg.mtext);
			wait(&status);
			printf("wait for child %d\n",status);
		}
	}

	else if(fork_flag == 0){
		printf("I am child\n");
		share_data--;
		printf("%d\n",share_data);
	
		msg recv_msg;
		msgflag = IPC_CREAT | 0666;
		msgid = msgget(key,msgflag);
		if(msgid < 0){
			perror("msgget");
			exit(1);
		}

		if(msgrcv(msgid,&recv_msg,MAX_BUFFER,1,0) < 0){
			perror("msgrcv");
			exit(1);
		}
		else{
			printf("success to recv / %s\n",recv_msg.mtext);
			exit(0);
		}
		
	}
	
	return 0;
}
