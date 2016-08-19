#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef struct node_st {
      int data;
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

static void revert(node_t *root)
{
    if (root == NULL) {
        return;
    }

    node_t *tmp = root->left;
    root->left = root->right;
    root->right = tmp;

    revert(root->left);
    revert(root->right);
}

static void travel(node_t *root)
{
      if (root == NULL) {
	    return;
      }

      travel(root->left);
      printf("%d ", root->data);
      travel(root->right);
}

static void scal_travel(node_t *root)
{
      QUEUE *q;
      node_t *pos;

      if (root == NULL) {
	    return;
      }

      q = queue_creat(sizeof(node_t *));
      if (0) {

      }

      printf("%x ", root->data);
      queue_en(q, &root);
      while (!queue_de(q, &pos)) {
	    if (pos->left != NULL) {
		  printf("%x ", pos->left->data);
		  queue_en(q, &pos->left);
	    }
	    if (pos->right != NULL) {
		  printf("%x ", pos->right->data);
		  queue_en(q, &pos->right);
	    }
      }
      putchar('\n');

      queue_destroy(q);
}

static void save(const char *path, node_t *root)
{
      QUEUE *q;
      node_t *pos;
      FILE *fp;

      if (root == NULL) {
	    return;
      }

      q = queue_creat(sizeof(node_t *));
      if (0) {

      }
      fp = fopen(path, "w");
      if (0) {

      }

      fwrite(root, sizeof(node_t), 1, fp);
      queue_en(q, &root);
      while (!queue_de(q, &pos)) {
	    if (pos->left != NULL) {
		  fwrite(pos->left, sizeof(node_t), 1, fp);
		  queue_en(q, &pos->left);
	    }
	    if (pos->right != NULL) {
		  fwrite(pos->right, sizeof(node_t), 1, fp);
		  queue_en(q, &pos->right);
	    }
      }

      fclose(fp);
      queue_destroy(q);
}

static node_t *load(const char *path)
{
      FILE *fp;
      QUEUE *q;
      node_t *root, *pos;

      q = queue_creat(sizeof(node_t *));
      if (0) {

      }

      fp = fopen(path, "r");
      if (0) {

      }

      root = malloc(sizeof(node_t));
      if (0) {

      }
      fread(root, sizeof(node_t), 1, fp);
      queue_en(q, &root);
      while (!queue_de(q, &pos)) {
	    if (pos->left != NULL) {
		  pos->left = malloc(sizeof(node_t));
		  fread(pos->left, sizeof(node_t), 1, fp);
		  queue_en(q, &pos->left);
	    }
	    if (pos->right != NULL) {
		  pos->right = malloc(sizeof(node_t));
		  fread(pos->right, sizeof(node_t), 1, fp);
		  queue_en(q, &pos->right);
	    }
      }

      fclose(fp);
      queue_destroy(q);
      return root;
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
      printf("%d\n\n", root->data);
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
	    insert(&root, arr[i]);
      }

//      travel(root);
      //putchar('\n');
      draw(root);
      balance(&root);
      draw(root);
      revert(root);
      draw(root);
//      scal_travel(root);
      //save("tmp", root);

      return 0;
}
