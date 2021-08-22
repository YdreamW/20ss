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

    plt.savefig("result2.png")


    
'''
    Main part. The algorithm used is an approximate 
    algorithm, which sorts all rectangles according
    to the height as the key word from large to small,
    and then arranges them to the first row that can fit
    it. If more rectangles cannot be put down, a new row
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
    loca[0][0] = loca[0][1] = 0
    curx = []
    cury = []
    tot = -1
    tmp = 0
    ans = 0
    for i in range(0,n):
        flag = 0
        # Find the first row that can fit it.
        for j in range(0, tot+1):       
            if (curx[j]+rect[i][0] <= width):
                loca[i][0] = curx[j]
                loca[i][1] = cury[j]
                curx[j] = curx[j] + rect[i][0]
                flag = 1
                break

        # Otherwise create a new row
        if (flag == 0):
            tot = tot+1
            curx.append(0)
            cury.append(tmp)
            if (tot >= 1):
                cury[tot] = cury[tot] + cury[tot-1]
            tmp = rect[i][1]
            loca[i][0] = curx[tot]
            loca[i][1] = cury[tot]
            curx[tot] = curx[tot] + rect[i][0]
            ans = max(ans, cury[tot]+tmp)

    end = time.time()

    print("The height of program2 is: ",ans)
    print("The time of program2 is: ",end-start)
    print('The rectangles and their locations:')
    print(rect)
    print(loca)
    print('\n')
    printResult(rect, loca, width)