import threading
import time

# global variables
flag = [False, False]
turn = 0
context_switch = 5

def peterson_solution(process):
    global flag, turn, context_switch
    print()
    print(f"Process {process} is in the Peterson Solution Right Now")
    other = 1 - process
    print(f"The other process id is {other}")
    print()
    # nijer flag ta true kore dibe

    flag[process] = True
    print("The flag has been updated, now 'flag[i] = True'") 
    print(f"The flag of {process} is True")
    print(f"Curent state of the Flag array : {flag}")
    print()

    # turn change korbe
    turn = other
    print("Updated the turn, 'turn = j' now")
    print(f"The turn is {turn}")
    print()

    # trap while loop / entry function
    while(flag[other] and turn == other):
        print(f"Process {process} is waiting")
        print(f"Because the flag of {other} is {flag[other]} and the turn is {turn}")
        print("Busy Wait situation")
        print()
        time.sleep(context_switch)
    
    # critical section
    print(f"Process {process} is in the critical section")
    print("Current state")
    print(f"Flag : {flag}")
    print(f"Turn : {turn}")
    print()
    print(f"Flag of the process {process} in critical section is {flag[process]}")
    time.sleep(context_switch)
    print(f"Process {process} is out of the critical section")
    # print()

    flag[process] = False
    print(f"The flag of {process} is False")
    print(f"Curent state of the Flag array : {flag}")
    print(f"Process {process} is out of the Peterson Solution and terminated")
    print()


context_switch = int(input("Enter the context switch time (preferred 4+) : "))
thread1 = threading.Thread(target=peterson_solution, args=(0,))
thread2 = threading.Thread(target=peterson_solution, args=(1,))
print("Threads created")
# print(f"IDs of the processes are {thread1.ident} and {thread2.ident}")
print("No threads have been started yet")
print("current state")
print(f"Flag : {flag}")
print(f"Turn : {turn}")
print()
thread1.start()
# print("Thread 1 started")
thread2.start()
# print("Thread 2 started")
# print()

thread1.join()
thread2.join()
print("Both threads are done")
    
