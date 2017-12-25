Tree* GetFunc_O(TokenStream* tsin)
{
	assert(tsin);
	ts = tsin;

	Tree* tree = CreateTree();
	assert(tree);

	NodeL* nowToken = nextToken(ts);
	Node *nowRoot = NULL;
	do
	{
		if (nowToken = NULL)
		{
			assert(!"SYNTAX ERROR [GetFunc_O]: File is empty;\n");
		}
		if (nowToken->type != FUNC)
		{
			assert(!"SYNTAX ERROR [GetFunc_O]: Can't find FUNC node;\n");
		}

		Node* func = ConvertToTreeNode(nowToken);
		NodeAddL(func, GetFunc_ID());
		NodeAddR(func, GetOP());

		nowToken = nextToken(ts);
		if (!nowToken || nowToken->type != CMD_END)
		{
			assert(!"SYNTAX ERROR [GetFunc_O]: Can't find CMD_END node;\n");
		}
		
		Node* root = ConvertToTreeNode(nowToken);
		NodeAddL(root, func);

		if (tree->root == NULL)
		{
			TreeAddRoot(tree, root);
			Node *nowRoot = tree->root;
		}
		else
		{
			NodeAddR(nowRoot, root);
			nowRoot = root;
		}

		nowToken = nextToken(ts);
	} while (nowToken == NULL);
	
	return tree;
}