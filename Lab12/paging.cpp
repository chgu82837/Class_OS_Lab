#include <stdio.h>
#include <time.h>
#include <cstdlib>

#define PAGE_SIZE 2
#define MEM_SIZE 32
#define PAGE_PER_PROCESS 8
#define PROCESS_AMOUNT 2

char phy_mem[MEM_SIZE];

class pages
{
public:
    pages(char* phy_mem){
        ffl = new int[MEM_SIZE/PAGE_SIZE];
        ffi = 0;
        mem = phy_mem;
        allo_map = new char[MEM_SIZE/PAGE_SIZE];
        for (int i = 0; i < MEM_SIZE/PAGE_SIZE; ++i){
            ffl[i] = -1;
            allo_map[i] = 0;
        }
    }

    void set_free_frame_list(int* free_frame_list,int free_frame_number){
        for (int i = 0; i < MEM_SIZE/PAGE_SIZE && i < free_frame_number; ++i)
        {
            ffl[i] = free_frame_list[i];
        }
        ffi = 0;
    }

    int allocate(char id){
        int result;
        if(ffl[ffi] != -1){
            allo_map[ffl[ffi]] = id;
            printf("Paging out and location allocated %d", ffl[ffi]);
            result = ffl[ffi];
            
        }
        else{
            int i = 0;
            for (int i = 0; i < MEM_SIZE/PAGE_SIZE; ++i)
                if(!allo_map[i]){
                    allo_map[i] = id;
                    ffl[ffi] = i;
                    printf("location allocated %d", i);
                    result = i;
                    goto allocate_success;
                }
                else{
                    printf("... ");
                }
            throw "NO MORE PAGE AVAILIBLE!";
        }
        allocate_success:
        if(++ffi >= MEM_SIZE/PAGE_SIZE)
            ffi = 0;
        return result;
    }

    void dump(){
        printf("frame list =====================================\n");
        for (int i = 0; i < MEM_SIZE/PAGE_SIZE; ++i)
        {
            if(ffi == i)
                printf("[%d] ",ffl[i]);
            else
                printf(" %d  ",ffl[i]);
        }
        printf("\nPhysical Memory & Allocation map ===============\n");
        printf(" Phy_addr | Owner | Content\n");
        char tmp;
        for (int i = 0; i < MEM_SIZE/PAGE_SIZE; ++i)
        {
            tmp = allo_map[i];
            tmp = tmp ? tmp : '-';
            printf(" %-8X | %c     | ",i,tmp);
            for (int j = 0; j < PAGE_SIZE; ++j)
            {
                printf("%c",mem[i*PAGE_SIZE + j]);
            }
            printf("\n");
        }
        printf("===============================================\n\n");
    }

private:
    int* ffl;
    int ffi;
    char* allo_map;
    
    char* mem;
};

class process
{
public:
    process(char identity,int max_heap,char* phy_mem){
        id = identity;
        allocated = 0;
        m2pages = new int[max_heap];
        mem = phy_mem;
    }

    void allocate(pages* pager){
        m2pages[allocated++] = pager->allocate(id);
        printf(" on Process %c.\n",id );
    }

    void set(int addr,char* value){
        for (int i = 0; i < PAGE_SIZE; ++i)
            mem[m2pages[addr]*PAGE_SIZE+i] = value[i];
    }

    char* get(int addr){
        char* r = new char[3];
        int i;
        for (i = 0; i < PAGE_SIZE; ++i)
            *(r+i) = mem[m2pages[addr]*PAGE_SIZE+i];
        *(r+i) = 0;
        return r;
    }

    void dump(){
        printf("Process pages ================\n");
        printf(" Logical | Physical | Content\n");
        for (int i = 0; i < allocated; ++i)
            printf(" %-7X | %-8X | %s\n",i,m2pages[i],get(i));
        printf("==============================\n\n");
    }
    
private:
    char id;
    int allocated;
    int* m2pages;
    char* mem;
};

int main(int argc, char const *argv[])
{
    process* A = new process('A',PAGE_PER_PROCESS,phy_mem);
    process* B = new process('B',PAGE_PER_PROCESS,phy_mem);
    pages* pager = new pages(phy_mem);

    int free_frame_list[] = {4,7,8,5,1,2,11,12,10,13,14,15};
    pager->set_free_frame_list(free_frame_list,sizeof(free_frame_list)/sizeof(int));
    
    srand(time(NULL));
    char input[PROCESS_AMOUNT+1];
    char p_id;
    int location;

    printf("\n============ Allocation Phase ============\n");
    for (int i = 0; i < PAGE_PER_PROCESS; ++i){
        A->allocate(pager);
        B->allocate(pager);
    }

    printf("\n============ Set Phase ============\n");
    for (int i = 0; i < MEM_SIZE/PAGE_SIZE; ++i)
    {
        if(argc >= 2){
            input[0] = 'A' + rand()%27;
            input[1] = 'A' + rand()%27;
            input[2] = 0;
            p_id = 'A' + i%PROCESS_AMOUNT;
            location = i/PROCESS_AMOUNT;
            printf("using precess %c, logical addr %X and value %s\n",p_id,location,input);
        }else{
            printf("Please input the process, logical addr and value (A 0 ha):");
            scanf("%c %d %s",&p_id,&location,input);
        }

        if(p_id == 'A'){
            A->set(location,input);
        }
        else{
            B->set(location,input);
        }
    }
    printf("\n============ Dumping Process A ============\n");
    A->dump();
    printf("============ Dumping Process B ============\n");
    B->dump();
    printf("============ Dumping Pager ============\n");
    pager->dump();
    if(argc < 2)
        printf("Using [this_exe --auto] to randomly auto generate test value\n");
    return 0;
}
