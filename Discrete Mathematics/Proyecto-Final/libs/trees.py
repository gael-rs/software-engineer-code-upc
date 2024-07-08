from anytree import Node, AnyNode
import random


# ÁRBOLES: Definir n elementos (10 <= n <= 15),
# con todos los elementos anteriores determinar un n-árbol T(2 <= n <= 4):

# Del árbol T definido:
# - Presentar los elementos de T por extensión.
# - Trazar su dígrafo.
# - Determinar su árbol B(T).
# - Determinar el arreglo LEFT - FATA - RIGHT
# - Que aplicaciones tiene el arreglo LEFT - DATA - RIGHT en el contexto real
# 
# 

#TO-DO:   DETERMINAR LEFT - DATA - RIGHT

def nodes_tree():
  n_total = random.randint(10,15)
  return n_total

def children_nodes():
  children = random.randint(2,4)
  return children


def n_tree(amount_nodes, max_children_each_node):
  root = Node("R")
  parentsPossibles = []
  parent = root
  maxReached = False
  
  children_each_node = random.randint(1, max_children_each_node)
  
  for i in range(amount_nodes):
    
    if len(parent.children) < children_each_node:
      nodoCurrently = Node(i+1, parent=parent)
      parentsPossibles.append(nodoCurrently)
    
    elif len(parentsPossibles) > 0:
      
      parent = parentsPossibles.pop(0)
      nodoCurrently = Node(i+1, parent=parent)
      parentsPossibles.append(nodoCurrently)
      
      children_each_node = random.randint(int(parent == root), max_children_each_node)
      
      if not maxReached and i + max_children_each_node * 2 > amount_nodes:
        children_each_node = max_children_each_node
        
      maxReached = children_each_node == max_children_each_node
      
  return root

def for_each_nodes(root, cb):
  parent = root
  childActual: Node = root.children[0]
  parentsPossibles = []
  
  while childActual != None:
    parentsPossibles.append(childActual)
    cb(childActual, parent)
    
    n = slice(parent.children.index(childActual) + 1, len(parent.children))
    
    childActual = parent.children[n][0] if len(parent.children[n]) > 0 else None
    
    if childActual == None:
      parent = parentsPossibles.pop(0)
      
      while len(parent.children) == 0 and len(parentsPossibles) > 0:
        parent = parentsPossibles.pop(0)
      
      childActual = parent.children[0] if len(parent.children) > 0 else None
      
def n_tree_binary(root_base: Node):
  idx = 2
  root = AnyNode(name="R", idx=idx, left=None, right=None)
  idx += 1
  parentActual = root
  parentsPossibles = [root]
  parentActualOld = None
  
  def callbackNode (nodeActual: Node, parent: Node):
    nonlocal parentActualOld, parentsPossibles, parentActual, idx
    
    if len(parentsPossibles) > 0 and parent != parentActualOld:
      parentActual = parentsPossibles.pop(0)
      childToAgainPush = parentActual.children[0] if len(parentActual.children) > 0 else None
      
      if childToAgainPush != None: 
        parentActual.children = []
        childToAgainPush.parent = None
      
      node = AnyNode(name=nodeActual.name, parent=parentActual, left=None, right=None, idx=idx)
            
      if childToAgainPush != None:
        childToAgainPush.parent = parentActual
        parentActual.right = childToAgainPush
        parentActual.left = node
        
      else:
        parentActual.left = node
    
    else:
      node = AnyNode(name=nodeActual.name, parent= parentActual, left=None, right=None, idx=idx)
      parentActual.right = node
    
    parentsPossibles.append(node)
    parentActual = node
    
    parentActualOld = parent
    
    idx += 1
  
  for_each_nodes(root_base, callbackNode)
  
  return root
    
def create_tree():
  amount_nodes = nodes_tree()
  children_each_node = children_nodes()
  root = n_tree(amount_nodes, children_each_node)
  
  root.get_n = lambda: children_each_node
  
  return root
  
def tree_for_extension(root: Node):
  
  result = "R = { "
  parent = root
  childActual: Node = root.children[0]
  parentsPossibles = []
  
  while childActual != None:
    result += f"({parent.name}, {childActual.name})"
    
    parentsPossibles.append(childActual)
    
    n = slice(parent.children.index(childActual) + 1, len(parent.children))

    childActual = parent.children[n][0] if len(parent.children[n]) > 0 else None
    
    if childActual == None:
      parent = parentsPossibles.pop(0)
      
      while len(parent.children) == 0 and len(parentsPossibles) > 0:
        parent = parentsPossibles.pop(0)
      
      childActual = parent.children[0] if len(parent.children) > 0 else None
      result += "" if childActual == None else ", "
    
    else:
      result += ", "
    
  result += " }"
  
  return result

def generate_ldr(root: AnyNode):

  nodeColumns = [
    [ 1, root.idx, 0, 0],
    [ 2, int(isinstance(root.left, AnyNode)) and root.left.idx, 
     root.name, 
     int(isinstance(root.right, AnyNode)) and root.right.idx],
  ]
  
  def read_node(node: AnyNode, _):
    
    nodeRow  = [
      node.idx,
      int(isinstance(node.left, AnyNode)) and node.left.idx,
      node.name, 
      int(isinstance(node.right, AnyNode)) and node.right.idx
    ]

    nodeColumns.append(nodeRow)
    
  for_each_nodes(root, read_node)
  
  
  nodeColumns = sorted(nodeColumns, key=lambda nodeColumn: nodeColumn[0])
  
  return nodeColumns;
