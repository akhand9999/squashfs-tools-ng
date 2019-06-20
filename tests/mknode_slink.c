/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "fstree.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(void)
{
	tree_node_t *node;
	struct stat sb;
	fstree_t fs;

	memset(&fs, 0, sizeof(fs));
	memset(&sb, 0, sizeof(sb));
	sb.st_mode = S_IFLNK | 0654;
	sb.st_uid = 123;
	sb.st_gid = 456;
	sb.st_rdev = 789;
	sb.st_size = 1337;

	node = fstree_mknode(&fs, NULL, "symlink", 7, "target", &sb);
	assert(node->uid == sb.st_uid);
	assert(node->gid == sb.st_gid);
	assert(node->mode == sb.st_mode);
	assert(node->parent == NULL);
	assert((char *)node->name >= (char *)node->payload);
	assert(node->data.slink_target >= (char *)node->payload);
	assert(node->name >= node->data.slink_target + 7);
	assert(strcmp(node->name, "symlink") == 0);
	assert(strcmp(node->data.slink_target, "target") == 0);
	free(node);

	node = fstree_mknode(&fs, NULL, "symlink", 7, "", &sb);
	assert(node->uid == sb.st_uid);
	assert(node->gid == sb.st_gid);
	assert(node->mode == sb.st_mode);
	assert(node->parent == NULL);
	assert((char *)node->name >= (char *)node->payload);
	assert(node->data.slink_target >= (char *)node->payload);
	assert(node->name >= node->data.slink_target + 1);
	assert(strcmp(node->name, "symlink") == 0);
	assert(node->data.slink_target[0] == '\0');
	free(node);

	return EXIT_SUCCESS;
}