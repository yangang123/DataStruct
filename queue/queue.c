#include <stdio.h>
#include <stdbool.h>

#define QUEUE_MAX_LEN  10

typedef struct  {
    int data;
    struct node *next;
}node_t;

typedef struct {
    int size;
    node_t *head;
    node_t *tail;
}queue_t;


queue_t *queue_create(void)
{
    queue_t *queue;

    queue = malloc(sizeof(queue_t));
    if ( !queue) {
        return NULL;
    } 
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
     
    return queue;
}

//队列是否是空
bool queue_empty(queue_t *queue) 
{
    return queue->size == 0;
}

//添加1个节点的数据data
int queue_add(queue_t *queue, int data)
{
    node_t *node;

    node = malloc(sizeof(node_t));
    if (!node) {
        return -1;
    }
    printf("node address:0x%x\n", node);
    node->data = data;
    node->next = NULL;
    if (!queue->head) {
        queue->head = node;
    } else {
        queue->tail->next = node;
    }
    queue->tail = node;
    
    queue->size++;
}

//从队列的
int queue_delete(queue_t *queue)
{
    int data = 0;

    if (queue_empty(queue)) {
        return -1;
    }
    //获取节点的数据
    data = queue->head->data; 
    
    //释放节点
    node_t *node = queue->head;
    if ( queue->head ==  queue->tail) {
        queue->tail = NULL;
    }
    queue->head = node->next;
    free(node); 
    queue->size--;

    return data;
}

int main(){
	int data[10]={1,2,3,4,5,6,7,8,9,10};
	int i=0;
    int read_data[10] = {0};

    queue_t *queue = queue_create();
    while(i < 5){
        queue_add(queue, data[i]);
        printf("input data queue[%d]:%d\n", i, data[i]);
        i++;
    }

    while(!queue_empty(queue))
          printf("output data queue：%d\n",queue_delete(queue)); 
  
}


