from PySide6.QtWidgets import QWidget, QVBoxLayout, QTreeWidget, QTreeWidgetItem


class OutlinerPanel(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.layout = QVBoxLayout(self)
        self.tree = QTreeWidget()
        self.tree.setHeaderLabel("Skeleton Hierarchy")
        self.layout.addWidget(self.tree)
        
    def populate_skeleton(self, skeleton_instance):
        self.tree.clear()
        if not skeleton_instance:
            return
        try:
            joints = skeleton_instance.joints
            items = {}
            for joint in joints:
                item = QTreeWidgetItem([joint.name])
                items[joint.index] = item
                if joint.parentIndex < 0:
                    self.tree.addTopLevelItem(item)
                else:
                    if joint.parentIndex in items:
                        items[joint.parentIndex].addChild(item)
        except Exception as e:
            print(f"Error populating skeleton: {e}")
        self.tree.expandAll()
