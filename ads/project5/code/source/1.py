import matplotlib.pyplot as plt
import time

'''
    This part is the visualization part, which 
    displays the results in the form of images.

    params
        rect: A list of rectangular lengths and 
              widths
        loca: A list of coordinates in the lower
              left corner of a rectangle
        width:A width limit given by the input

'''
def printResult(rect, loca, width): 

    # A list is used to store some selected colors
    mycolor = ["aquamarine", "dodgerblue", "rosybrown", "maroon", "khaki", \
        "mediumpurple", "cornflowerblue", "slategrey", "tan", "salmon"]
    color_num = len(mycolor)

    # Set the size of the canvas based on the output 
    # rectangle collection
    mxa = 0
    mxb = 0
    for i in range(0, len(rect)):
        mxa = max(rect[i][0]+loca[i][0], mxa)
        mxb = max(rect[i][1]+loca[i][1], mxb)
    
    fig = plt.figure(figsize=(4, 8))

    ax1 = fig.add_subplot(111)
    ax1.set_xlim([0, width])
    ax1.set_ylim([0, 1.6*mxb])

    # Print rectangle on frequency screen
    cur = 0
    for i in range(0, len(rect)):
        tmp = plt.Rectangle((loca[i][0], loca[i][1]), rect[i][0], rect[i][1], \
            facecolor=mycolor[cur], edgecolor="white")
        ax1.add_patch(tmp)
        cur = (cur+1)%color_num

    plt.savefig("result1.png")

'''
    Main part. The algorithm used is an approximate 
    algorithm, which sorts all rectangles according
    to the height as the key word from large to small,
    and then arranges them in order from left to right. 
    If more rectangles cannot be put down, a new row
    will be created.
'''
if __name__=='__main__':


    # input data
    # rect[] stores the length and width of the rectangle, 
    # and loca[] stores the coordinates of the lower left
    # corner of the rectangle.
    rect = []
    loca = []

    n,width = list( map(int, input().split() ) )
    start = time.time()
    for i in range(0,n):
        rect.append( list( map(int, input().split() ) ) )
        
    # Sort by height
    rect.sort(key=lambda x:x[1], reverse=True)
    loca.append([0, 0])
    for i in range(1,n):
        loca.append([loca[i-1][0]+rect[i-1][0], 0])

    # Arrange in order
    ans = 0
    loca[0][0] = loca[0][1] = 0
    curx = 0
    cury = 0
    tmp = rect[0][1]
    for i in range(0,n):
        if (curx+rect[i][0] <= width): # The current line can fit
            loca[i][0] = curx
            loca[i][1] = cury
            curx = curx + rect[i][0]
        else:                          # Create a now row
            curx = 0
            cury = cury + tmp
            tmp = rect[i][1]
            loca[i][0] = curx
            loca[i][1] = cury
            curx = curx + rect[i][0]
            ans = max(ans, cury+tmp)
    end = time.time()
    print("The height of program1 is: ",ans)
    print("The time of program1 is: ",end-start)
    print('The rectangles and their locations:')
    print(rect)
    print(loca)
    print('\n')
    printResult(rect, loca, width)