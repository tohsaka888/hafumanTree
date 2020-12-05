#include <stdio.h>
#include <stdlib.h>
typedef struct Tree {
    char data;
    int parent;
    int weight;
    int leftchild;
    int rightchild;
}tree;

typedef struct HuffTree {
    int n;
    int root;
    tree *ht;
}hufftree;

hufftree* CreateHuffTree(int n,int w[],char data[])
{
    hufftree* pht;
    int i = 0, j = 0;	//定义循环变量
    int x1, x2, min1, min2;	//定义最小值下标、次小值下标、最小值、次小值
    pht = (hufftree *)malloc(sizeof(hufftree));
    if (pht == NULL)
    {
        printf("pht malloc Out of space!\n");
        return pht;
    }
    pht->ht = (tree*)malloc(sizeof(tree) * (2 * n - 1));	//为哈夫曼树分配2n-1个结点空间
    if (pht->ht == NULL)
    {
        printf("ht malloc Out of space!\n");
        return pht;
    }
    //初始化哈夫曼树
    for (i = 0; i < 2 * n - 1; i++)
    {
        pht->ht[i].leftchild = -1;	//初始化叶结点左孩子
        pht->ht[i].rightchild = -1;	//初始化叶结点右孩子
        pht->ht[i].parent = -1;		//初始化叶结点的父结点
        if (i < n)
        {
            pht->ht[i].weight = w[i];	//赋值叶子结点的权值
            pht->ht[i].data = data[i];	//初始化叶子结点的data
        }
        else
        {
            pht->ht[i].weight = -1;		//初始化内部结点的权值为-1
        }
    }
    //构造内部结点
    for (i = 0; i < n - 1; i++)
    {
        min1 = 100;	//初始化最小值为100
        min2 = 100;	//初始化次小值为100
        x1 = -1;	//初始化最小值下标为-1
        x2 = -1;	//初始化次小值下标为-1
        for (j = 0; j < n + i; j++)
        {
            //找到最小值下标赋值给x1,最小值赋值给min1
            if (pht->ht[j].weight < min1 && pht->ht[j].parent == -1 )
            {
                min2 = min1;
                x2 = x1;
                min1 = pht->ht[j].weight;
                x1 = j;
            }
                //找到次小值下标赋值给x2,最次值赋值给min2
            else if (pht->ht[j].weight < min2 && pht->ht[j].parent == -1 )
            {
                min2 = pht->ht[j].weight;
                x2 = j;
            }
        }
        pht->ht[n + i].weight = min1 + min2;	//初始化父结点的权值
        pht->ht[n + i].leftchild = x1;			//给父结点左孩子赋值
        pht->ht[n + i].rightchild = x2;			//给父结点右孩子赋值
        pht->ht[x1].parent = n + i;				//给左孩子的父结点赋值
        pht->ht[x2].parent = n + i;				//给右孩子的父结点赋值
    }
    pht->root = 2 * n - 2;							//根节点位置
    pht->n = n;										//哈夫曼树的叶子结点数
    return pht;
}

//该函数用于输出叶子结点的哈夫曼编码
void PrintHuffCode(int n,hufftree *pht)
{
    int i = 0, num = 0, j = 0;	//定义循环变量
    int parent = 0;				//定义父结点下标临时变量
    int times = 0;				//记录每个结点哈夫曼编码的长度
    int code[10];
    for (i = 0; i < n; i++)		//循环给每个叶子结点进行编码
    {
        num = i;				//初始化用于控制循环的变量
        j = 0;					//初始化用于控制数组code的变量
        times = 0;
        while (pht->ht[num].parent != -1)					//循环到当前结点的父结点为-1
        {
            parent = pht->ht[num].parent;
            if (pht->ht[parent].leftchild == num)			//当前结点为父结点的左孩子，编码为0
            {
                code[j] = 0;
                j++;
                times++;									//编码长度加1
            }
            else if (pht->ht[parent].rightchild == num)		//当前结点为父结点的右孩子，编码为1
            {
                code[j] = 1;
                j++;
                times++;									//编码长度加1
            }
            num = parent;									//将num赋值为父结点下标
        }
        printf("%c:", pht->ht[i].data);		//输出第i个叶子结点的data
        for (j = times-1; j >= 0; j--)		//输出第i个叶子结点的哈夫曼编码
        {
            printf("%d", code[j]);
        }
        printf("\n");
    }
}
void PrintHuffTree(hufftree *pht,int n)
{
    for (int i = 0; i < 2 * n - 1; i++)
    {
        printf("第%d个结点:weight=%d  parent= %d  leftchild=%d  rightchild=%d\n", i, pht->ht[i].weight, pht->ht[i].parent, pht->ht[i].leftchild, pht->ht[i].rightchild);
    }
    return;
}
int main()
{
    int i = 0;
    int w[10];
    char data[10];
    //依次输入结点的名称，不需要加空格
    for (i = 0; i < 10; i++)
    {
        scanf("%c", &data[i]);
    }
    //依次输入结点的权值
    for (i = 0; i < 10; i++)
    {
        scanf("%d", &w[i]);
    }
    /*for (i = 0; i < Maxn; i++)	//用于测试
    {
        printf("%c:%d\n", data[i], w[i]);
    }*/
    hufftree *pht = CreateHuffTree(i,w,data);
    printf("\n哈夫曼树为：\n");
    PrintHuffTree(pht,i);
    printf("\n对外部结点进行哈夫曼编码：\n");
    PrintHuffCode(i,pht);
    return 0;
}
