
var Node = function( key )
{
	this.key = key;
	this.left = null;
	this.right = null;
};

var Tree = function( )
{
	this.root = null;
};

Tree.prototype._insert = function( node, key )
{
	if( node == null )
	{
		return new Node( key );
	}

	if( node.key > key )
	{
		node.left = this._insert( node.left, key )
	}
	else if( node.key < key )
	{
		node.right = this._insert( node.right, key )
	}

	return node;
};

Tree.prototype.insert = function( key )
{
	this.root = this._insert( this.root, key );
};

Tree.prototype._print = function( node )
{
	if( node == null )
		return;
	this._print( node.left );
	console.debug( node.key );
	this._print( node.right );
};

Tree.prototype.print = function()
{
	this._print( this.root );
}

var tree = new Tree();
tree.insert( 5 );
tree.insert( 2 );
tree.insert( 1 );

console.debug( tree );