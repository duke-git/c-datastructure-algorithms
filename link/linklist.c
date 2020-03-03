#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linklist.h"


/**
 * create linklist
 */
LinkList create_linklist()
{
    int length;
    int data;
    int i;

    //创建头节点
    LinkList p_head = (LinkList) malloc(sizeof(Node));

    if (NULL == p_head) {
        printf("内存分配失败，程序退出！\n");
        exit(-1);
    }

    //创建尾节点
    LinkList p_tail = p_head;
    p_tail->next = NULL;

    printf("请输入想要创建链表结点的个数：length = ");
    scanf("%d", &length);

    for (i = 0; i < length; i++) {
        printf("请输入第%d个结点的值：", i+1);
        scanf("%d", &data);
        LinkList p_new = (LinkList)malloc(sizeof(Node));
        if(NULL == p_new) {
            printf("内存分配失败，程序退出！\n");
            exit(-1);
        }

        p_new->data = data;
        p_tail->next = p_new;
        p_new->next = NULL;
        p_tail = p_new;
    }

    return p_head;

}

/**
 * traverse linklist
 * @param p_head : head pointer of linklist
 */
void traverse_linklist(LinkList p_head)
{
    printf("============遍历链表=============\n");

    if (p_head == NULL || p_head->next == NULL) {
        printf("链表为空\n");
    }

    //设置当前节点为第一个节点
    LinkList p_current = p_head->next;

    while (p_current != NULL) {
        printf("存储数据值：%d, 存储的指针值：%p\n ", p_current->data, p_current->next);
        p_current = p_current->next; //移动当前节点
    }
}
/**
 * get the elements length of linklist
 * @param p_head : head pointer of linklist
 * @return
 */
int get_length(LinkList p_head)
{
    int len = 0;

    if (p_head == NULL || p_head->next == NULL) {
        printf("链表不存在\n");
        return len;
    }
    LinkList p_current = p_head->next;;
    //设置当前节点为第一个节点
    while (p_current != NULL) {
        len++;
        p_current = p_current->next;
    };

    return len;
}

/**
 * find element in linklist
 * @param p_head header pointer of linklist
 * @param value the find value
 * @return the find node
 */
LinkList find_element(LinkList p_head, int value)
{
    if (p_head == NULL || p_head->next == NULL) {
        printf("链表不存在\n");
        return NULL;
    }

    int index = 0;

    LinkList p_current = p_head->next;;

    while (p_current != NULL) {
        index++;
        if (p_current->data == value) {
            printf("查找到第%d个节点，存储数据值：%d, 存储的指针值：%p\n ", index, p_current->data, p_current->next);
            return p_current;
        }
        p_current = p_current->next;
    };

    return NULL;
}

/**
 * insert element into linklist
 * @param p_head
 * @param position insert position is position + 1
 * @param value
 * @return
 */
bool insert_element(LinkList p_head, int position, int value)
{
    printf("============插入链表元素%d=============\n", value);

    if (p_head == NULL || p_head->next == NULL) {
        printf("失败，链表不存在\n");
        return false;
    }

    int length = get_length(p_head);
    if (position < 0 || position > length) {
        printf("失败，链表插入元素位置范围为1～链表长度：1～%d\n", length);
        return false;
    }

    int index = 0;

    LinkList p_current = p_head;

    while (p_current != NULL) {
        if (index == position - 1) {
            LinkList p_new = (LinkList)malloc(sizeof(Node));
            if (p_new == NULL) {
                printf("内存分配失败，程序退出！\n");
                exit(-1);
            }
            p_new->data = value;
            p_new->next = p_current->next;
            p_current->next = p_new;
            printf("成功插入第%d个节点，存储数据值：%d, 存储的指针值：%p\n ", position, p_new->data, p_new->next);
            return true;
        }
        index++;
        p_current = p_current->next;
    };

    return false;
}

/**
 * delete element of linklist
 * @param p_head
 * @param position
 * @param value
 * @return
 */
bool delete_element(LinkList p_head, int position, int *value)
{

    if (p_head == NULL || p_head->next == NULL) {
        printf("链表不存在\n");
        return false;
    }

    int length = get_length(p_head);
    if (position < 0 || position > length) {
        printf("链表删除元素位置范围为1～链表长度：1～%d\n", length);
        return false;
    }

    int index = 0;

    LinkList p_current = p_head->next, p_pre = p_head;

    while (p_current != NULL) {
        if (index == position - 1) {
            p_pre->next = p_current->next;
            *value = p_current->data;
            free(p_current);
            printf("成功删除第%d个节点", position);
            return true;
        }
        index++;
        p_current = p_current->next;
        p_pre = p_pre->next;
    };

    return false;

}

/**
 * reverse linklist
 * @param p_head head pointer of linklist
 * @return head pointer of reversed linklist
 */
LinkList reverse_linklist(LinkList p_head)
{
    if (p_head == NULL || p_head->next == NULL) {
        printf("链表不存在\n");
        return NULL;
    }
    //初始化前驱，当前，后继节点
    LinkList p_pre = p_head->next;
    LinkList p_current = p_head->next->next;
    LinkList p_tmp = NULL;

    while (p_current != NULL) {
        //重置指针
        p_tmp = p_current->next;
        p_current->next = p_pre;
        //交换节点：前驱->当前，当前->后继
        p_pre = p_current;
        p_current = p_tmp;
    }

    p_head->next->next = NULL;
    p_head->next = p_pre;
    printf("反转链表结束\n");
    return p_current;
}

/**
 * bubble sort linklist
 * @param p_head head pointer of linklist
 */
LinkList sort(LinkList p_head)
{
    if (p_head == NULL || p_head->next == NULL) {
        printf("链表不存在\n");
    }

    int length = get_length(p_head);
    int i;

    LinkList p_tmp = NULL;
    LinkList p_current = p_head->next;

    for (i = 0; i < length-1; i++) {
        for (int j = 0; j < length-1-i; j++) {
            if(p_current->data > p_current->next->data) {
                p_tmp = p_current;
                p_current = p_current->next;
                p_current->next = p_tmp;
            }
        }
    }

    return p_head;

}

/**
 * Delete the element of position n in reverse order
 * leetcode 19
 * @param p_head : linklist head
 * @param n : position n in reverse order
 * @return linklist head
 */
LinkList delete_after_n(LinkList p_head, int n)
{
    if (p_head == NULL || p_head->next == NULL) {
        printf("链表不存在\n");
        return NULL;
    }
    LinkList p_pre = p_head, p_current = p_head;
    int i = 0;

    while (p_current->next != NULL) {
        i++;
        p_current = p_current->next;
        if (i > n) {
            p_pre = p_pre->next;
        }
    }

    if (i < n) {
        p_head = p_head->next;
        return p_head;
    }

    LinkList p_delete = p_pre->next;
    p_pre->next = p_delete->next;

    return p_head;
}


/**
 *
 * @param p_head
 * @return
 */
bool is_empty(LinkList p_head)
{
    if (p_head->next == NULL) {
        return true;
    } else {
        return false;
    }
}
