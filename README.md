# OOP-AVL-Countdown-Tree
Overview

In this project, you and your partner will implement a variant of an AVL tree called a countdown tree.  Similar to an AVL tree, a countdown tree keeps track of its height and works to ensure that the height of the left and right subtrees differ by at most 1 for every node in the tree.  Unlike an AVL tree, though, the countdown tree does not ensure this property after every operation, and only uses standard BST insertion and deletion.  Instead, it keeps a countdown that decreases after every insertion and deletion, and when that countdown reaches 0, it rebalances all of its nodes at once.

Rebalancing the tree

When the countdown reaches 0, the rebalancing process iterates through the tree in a post-order traversal.  First, it calculates a balance value from the height of its children.  If this balance is +/- 2, it performs 1-2 tree rotations to fix the balance and continues its traversal.  The cases for tree rotations are exactly the same as for an ordinary AVL tree.  Use the nodes' balance to determine if this is a LL, RR, LR, or RL case, and perform the same rotations as in an AVL tree. If a node's child has a balance of 0, treat this as a "matched" (LL or RR) case.

After performing the rotations, recalculate the heights of the 2-3 nodes involved in the rotation (parent and child in LL and RR cases, or parent, child, and grandchild in LR and RL cases) before continuing the rebalancing traversal.  If no rotation was needed (balance of 0, 1, or -1), calculate the height of this node based on its left and right children. Every node has height = 1 + max(left->height, right->height), where null pointers are considered height 0.

Important:  when updating the heights of the nodes involved in a rotation, be sure that the heights are updated from bottom to top (relative to where they end up)--you cannot calculate a parent's height correctly if its child's height is wrong.

After rebalancing the tree, reset the countdown to 10 or the height of the tree, whichever is larger.

