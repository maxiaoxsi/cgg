import sys
from PyQt5.QtWidgets import QApplication, QTreeWidget, QTreeWidgetItem

def parse_to_tree_structure(lines):
    root = None
    stack = []
    for line in lines:
        if not line.strip():
            continue
        depth = line.count('  ')
        node = QTreeWidgetItem([line.strip()])

        if depth == 0:
            root = node
            stack = [root]
        else:
            while len(stack) > depth:
                stack.pop()
            stack[-1].addChild(node)
            stack.append(node)

    return root

def create_tree_view(data):
    app = QApplication(sys.argv)
    tree = QTreeWidget()
    tree.setHeaderLabel('Syntax Tree')
    root = parse_to_tree_structure(data)
    tree.addTopLevelItem(root)
    tree.expandAll()
    tree.resize(800, 600)  # 设置窗口的初始大小为800x600
    tree.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    if len(sys.argv) == 2:
        file_path = sys.argv[1]
    else:
        file_path = 'syntaxTree.txt'
    with open(file_path, 'r') as file:
        lines = file.readlines()
    create_tree_view(lines)
