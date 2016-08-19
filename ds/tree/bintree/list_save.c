#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef struct node_st {
      char data;
      struct node_st *left, *right;
} node_t;

static node_t *find_max(node_t *root)
{
      if (root->right == NULL) {
	    return root;
      }

      return find_max(root->right);
}

static node_t *find_min(node_t *root)
{
      if (root->left == NULL) {
	    return root;
      }

      return find_min(root->left);
}

static int insert(node_t **root, int data)
{
      node_t *newnode;

      if (*root == NULL) {
	    newnode = malloc(sizeof(node_t));
	    newnode->data = data;
	    newnode->left = NULL;
	    newnode->right = NULL;

	    *root = newnode;
	    return 0;
      }
      if (data <= (*root)->data) {
	    return insert(&(*root)->left, data);
      } else {
	    return insert(&(*root)->right, data);
      }
}

static void delete(node_t **root, int data)
{
      node_t *pos, *left, *right;

      if (*root == NULL) {
	    return;
      }

      if ((*root)->data == data) {
	    pos = *root;
	    left = pos->left;
	    right = pos->right;
	    if (left != NULL) {
		  *root = left;
		  find_max(left)->right = right;
	    } else {
		  *root = right;
	    }
	    free(pos);
	    return;
      } else if (data < (*root)->data) {
	    delete(&(*root)->left, data);
	    return;
      } else {
	    delete(&(*root)->right, data);
            return;
      }

}

static node_t *find(node_t *root, int data)
{
      if (root == NULL) {
	    return NULL;
      }

      if (root->data == data) {
	    return root;
      } else if (data < root->data) {
	    return find(root->left, data);
      } else {
	    return find(root->right, data);
      }
}

static void __save(FILE *fp, node_t *root)
{
      if (root == NULL) {
	    fwrite("()", 2, 1, fp);
	    return;
      }

      fwrite("(", 1, 1, fp);
      fwrite(&root->data, 1, 1, fp);
      __save(fp, root->left);
      __save(fp, root->right);
      fwrite(")", 1, 1, fp);
}

static void save(const char *path, node_t *root)
{
      FILE *fp;

      fp = fopen(path, "w");
      if (0) {

      }

      __save(fp, root);

      fclose(fp);
}

static void draw(node_t *root)
{
      static int indent = 0;
      int i;

      if (root == NULL) {
	    return;
      }

      indent++;
      draw(root->right);
      indent--;
      for (i = 0; i < indent; i++) {
	    putchar('\t');
      }
      printf("%c\n\n", root->data);
      indent++;
      draw(root->left);
      indent--;
}

static int node_num(node_t *root)
{
      if (root == NULL) {
	    return 0;
      }

      return node_num(root->left) + 1 + node_num(root->right);
}

static void turn_left(node_t **root)
{
      node_t *tmp = *root;

      *root = tmp->right;
      find_min(*root)->left = tmp;
      tmp->right = NULL;
}

static void turn_right(node_t **root)
{
      node_t *tmp = *root;

      *root = tmp->left;
      find_max(*root)->right = tmp;
      tmp->left = NULL;
}

static void balance(node_t **root)
{
      int sub;

      if (*root == NULL) {
	    return;
      }

      sub = node_num((*root)->left) - node_num((*root)->right);
      while (sub > 1 || sub < -1) {
	    if (sub > 1) {
		  turn_right(root);
	    } else {
		  turn_left(root);
	    }
	    sub = node_num((*root)->left) - node_num((*root)->right);
      }
      balance(&(*root)->left);
      balance(&(*root)->right);

}

int main(void)
{
      int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
      int i;
      node_t *root = NULL;
      node_t *new;

      for (i = 0; i < (sizeof(arr) / sizeof(int)); i++) {
	    insert(&root, arr[i] + '0');
      }

      draw(root);
      balance(&root);
      draw(root);
      save("tmp", root);

      return 0;
}
