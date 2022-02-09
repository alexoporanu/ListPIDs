#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

struct process_info {
	int dfs_level;  		// level of the current process in the dfs tree
	pid_t pid;			// pid of current process
	pid_t parent_pid; 		// pid of parent process
	pid_t child_process[505];  	// list of children pids
	int children;			// number of children 
	time_t time;			// time 
	size_t buffsize;		// buffer size	
};

void print(struct process_info p) {
	printf("\n********************************\n");	
	printf("Process ID : %d\n", p.pid);
	printf("Level in DFS tree: %d\n", p.dfs_level);
	printf("Parent ID : %d\n", p.parent_pid);
	printf("Number of children: %d\n", p.children);
	printf("Time: %jd\n", p.time);
	printf("Buffer size: %d\n", p.buffsize);
	printf("**********************************\n");	
	printf("\n\n");  
}

void dfs(pid_t pid, pid_t parent_pid, int dfs_level) {
    	struct process_info P;
    	P.pid = pid;
    	P.parent_pid = parent_pid;
    	P.dfs_level = dfs_level;
    	syscall(331, pid, &P);
    
    	print(P);

    	int i;
    	for (i = 0; i < P.children; ++i) {	
	        dfs(P.child_process[i], pid, dfs_level + 1);
    	}
}

int main() {
	int start = 37107;
    	if (kill(start, 0) < 0) {
		printf("The given PID does not exist!\n");
		return 0;
	}
	dfs(start, -1, 1);
	return 0;
}
