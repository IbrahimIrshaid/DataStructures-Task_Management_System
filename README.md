# Task Manager with Linked Lists & Stacks

![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)
![Data structures](https://img.shields.io/badge/structures-linked%20list%20%C2%B7%20stack-555)

This is a command-line to-do manager written in C, using only **hand-built singly linked lists and a stack**. There are no arrays of records and no library containers.

- **Unperformed tasks** are kept in a linked list: load, add, delete and search by ID or name.
- **Performing** a task pushes it onto a **stack**, so **undo** pops the most recent one and puts it back in the unperformed list (flagged as *undone*).
- **Summary report**: writes the unperformed, undone and performed tasks to `Report.txt`.

## Run

```bash
gcc P1_1231870_IbrahimIrshaid_1.c -o tasks && ./tasks
```

Pick option **1** first to load [`tasks.txt`](tasks.txt), which has one task per line in the form `id#name#date#duration-hours`:

```
101#Finish OS report#12/11/2025#3.5
```

A follow-up version that rebuilds this on a binary search tree is in [DataStructures-Task_Management_System_BST](https://github.com/IbrahimIrshaid/DataStructures-Task_Management_System_BST).

---

*Data Structures (COMP2421), Birzeit University, Spring 2025.*
