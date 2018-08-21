class Node(object):
	"""struct type"""
	def __init__(self, val):
		self.next = None
		self.val = val

class LinkedList(object):
	def __init__(self):
		self.head = None
		self.tail = None

	def add_node(self, val):
		if not self.head:
			self.__initialize_list(val)
		else:
			node = Node(val)
			self.tail.next = node
			self.tail = node

	def print_list(self):
		current_node = self.head

		print("head -> "),
		while current_node is not None:
			print(current_node.val),
			current_node = current_node.next
			print(" -> "),
		print("tail")

	def reverse(self):
		current_head = self.head
		head = self.head

		while current_head is not None:
			temp = current_head
			current_head = head.next
			t_next = current_head.next
			head.next = t_next
			current_head.next = temp

			if head.next is None:
				self.head = current_head
				break

	def __initialize_list(self, val):
		self.head = Node(val)
		self.tail = self.head

if __name__ == "__main__":
	l = LinkedList()
	l.add_node(1)
	l.add_node(2)
	l.add_node(3)
	l.add_node(4)
	l.add_node(5)
	
	l.print_list()
	l.reverse()
	l.print_list()