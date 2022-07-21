#include "imgUtils.c"

#ifndef SIZEX
  #define SIZEX 512
  #define SIZEY 512
#endif 

/*---------------------------------------------------------------------------*/

/**
 * This struct contains one node of the linked list, which represents a single 
 * command to the Turtle. It's field  include:
 * 
 *  - cmd   : A char array of size 10 holding the command name
 * 
 *  - val   : An integer that stores a parameter for the command (like forward,
 *            backward and colour). 
 * 
 *  - next  : A pointer to a struct of the same type, this is used for the 
 *            linked list
 ****/

typedef struct cmdnode {
    char cmd[10];
    int val;
    struct cmdnode *loop_head;
    struct cmdnode *next;
} CmdNode;

/*---------------------------------------------------------------------------*/

CmdNode *newCmdNode(char cmd[10], int val) {
  /**
   * This function allocates a new CmdNode struct and initializes it's values
   * based on the input paramaters given. The next pointer is always
   * initialized to NULL.
   */
    if((strcmp("penup",cmd)==0)||(strcmp("pendown",cmd)==0)||(strcmp("colour",cmd)==0)||(strcmp("forward",cmd)==0)||(strcmp("backward",cmd)==0)||(strcmp("right",cmd)==0)||(strcmp("left",cmd)==0)||(strcmp("loop",cmd)==0)) //Checking if the cmd value i'm getting is valid
    {
        CmdNode *NewCmdNode = NULL;//Make a Null Pointer ro CmdNode
        NewCmdNode = (CmdNode *) calloc(1,sizeof(CmdNode)); //Reserving space by calloc for that certain node
        strcpy(NewCmdNode->cmd,cmd);//Adding the Comand in that node
        NewCmdNode->val = val;//Adding the Value of the Command in that node
        NewCmdNode->loop_head = NULL;// Starting the loop as null
        NewCmdNode->next = NULL; //Making the Next Null of NewCmdNode
        return NewCmdNode;//Returning the Node so it can get added to the linked list
    }
    printf("Invalid command.\n"); //If that cmd value is invalid print this and retun Null
    return NULL;
}

/*---------------------------------------------------------------------------*/

void insertCommandLoop(CmdNode *loop_node,CmdNode *new_command_node)
{
    if(loop_node->loop_head == NULL)//If the loops head is NULL
    {
        loop_node->loop_head = new_command_node;//Make the new_command_node as the first node in the loop
    }
    else
    {
        CmdNode *p = NULL;
        p = loop_node->loop_head;//Make Pointer = loop head so we won't lose the head
        while (p->next!=NULL)//while we don't find the last pointer keep going
        {
            p = p -> next;//make p=next pointer in linked list
        }
        p->next = new_command_node;//when find the last one node make that equal to the new_command_node
    }
}

/*---------------------------------------------------------------------------*/

void printCommandList(CmdNode *head) {
  /**
   * This function prints out each command in the linked list one after the
   * other.
   */
    CmdNode *p = NULL;//Making a pointer to the CmdNode
    p = head;//Equal it to head, just so we don't lose the head (we might need for other examples)
    int count = 0;// Start Intial Value of the Count = 0
    while(p != NULL)//Keep going until pointer is null
    {
        if(p->val == 0)//If the value is 0, printing command with just name
        {
            printf("%3d: %s\n",count,p->cmd);
        }
        else //printing command with the name and val
        {
            printf("%3d: %s %d\n",count,p->cmd,p->val);
        }
        if (strcmp("loop",p->cmd)==0)//If the command is loop[means we have explore more]
        {
            CmdNode *p_loop = NULL;
            p_loop = p->loop_head;//saving the loop head
            while (p_loop!=NULL)//while the command of the loop don't end
            {
                count = count + 1;//keep the count up
                if(p_loop->val == 0)//If Val is 0 means we only need to print name
                {
                    printf("%3d:   %s\n",count,p_loop->cmd);
                }
                else//else we need to print the command plus the value
                {
                    printf("%3d:   %s %d\n",count,p_loop->cmd,p_loop->val);
                }
                p_loop = p_loop->next;//go the next loop
            }
        }
        p=p->next;//keep scrolling through the linked llist
        count = count + 1;//keep adding the count
    }
  return;
}

/*---------------------------------------------------------------------------*/

void queryByCommand(CmdNode *head, char cmd[10]) {
  /**
   * This function looks for commands in the linked list that match the input
   * query. It prints them out in the same format as the printCommandList()
   * function.
   */
    CmdNode *p = NULL;
    p = head;//Saving the head node
    int count = 0;
    while(p != NULL)
    {
        //Checking if Pointers Command = cmd
        if(strcmp(cmd,p->cmd)==0)
        {
            if(p->val == 0) //Print the Name of Command
            {
                printf("%3d: %s\n",count,p->cmd);
            }
            else//Printing the Name and Value of Command
            {
                printf("%3d: %s %d\n",count,p->cmd,p->val);
            }
        }
        if (strcmp("loop",p->cmd)==0)//If Pointer command is Loop
        {
            CmdNode *p_loop = NULL;
            p_loop = p->loop_head;//Save the Loop Head
            while (p_loop!=NULL)
            {
                count = count + 1;//Keep Counting
                if (strcmp(cmd,p_loop->cmd)==0)//Checking if Pointers Command = cmd
                {
                    if(p_loop->val == 0)//Print the Name of Command
                    {
                        printf("%3d: %s\n",count,p_loop->cmd);
                    }
                    else//Printing the Name and Value of Command
                    {
                        printf("%3d: %s %d\n",count,p_loop->cmd,p_loop->val);
                    }
                }
                p_loop = p_loop->next;//Going to the Next Loop Node
            }
        }
        p=p->next;//Going to the Next Node
        count = count + 1;//Keep Counting
    }
  return;
}

/*---------------------------------------------------------------------------*/

int countCommands(CmdNode *head) {
  /**
   * This function counts and returns the length of the linked list. It
   * requires list traversal.
   */
      CmdNode *p = NULL;
      p = head;//Saving the Head
      int count = 0;
      while(p != NULL)
      {
          count = count + 1;//Keep Counting for Each Node
          if (strcmp("loop",p->cmd)==0)//If the Command is Loop
          {
              CmdNode *p_loop = NULL;
              p_loop = p->loop_head;//Save the loops Command
              while (p_loop!=NULL)
              {
                  count = count + 1;//Keep Counting for Each Loop's Node
                  p_loop = p_loop->next;//Go to the next loop node
              }
          }
          p=p->next;//Go to the next node
      }
    return count;//Return the Total Count
}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommand(CmdNode *head, CmdNode *new_CmdNode) {
  /**
   * This function inserts the node new_CmdNode *at the tail* of the linked
   * list.
   */
      if(head == NULL)//If the head is Null
      {
          head = new_CmdNode; //Equal the head equal to the newnode I have
          return head; //return the head then
      }
      else // if head is not null (means there are more nodes in already)
      {
          CmdNode *p = NULL;//Making pointer p from CmdNode = Null
          p = head;//making p = head, so we don't lost head
          while (p->next != NULL)//keep going until the pointer's next is null
          {
              p = p->next; //making p = next pointer
          }
          p ->next = new_CmdNode; //make the last node's next = new_CmdNode
          return head;// return the head then
      }
    return NULL;//If anything goes wrong just return the Null(usally a calloc error)
    }

/*---------------------------------------------------------------------------*/


CmdNode *deleteCommandList(CmdNode *head) {
  /**
   * This function deletes the linked list of commands, releasing all the
   * memory allocated to the nodes in the linked list.
   */
      CmdNode *p = NULL;
      p = head;//Save the head
      while(p != NULL)
      {
          if (strcmp("loop",p->cmd)==0)//if the command is loop
          {
              CmdNode *next_head = NULL;//Pointer Holder
              CmdNode *p_loop = NULL;
              p_loop = p->loop_head;//Saving the Loop Head
              while (p_loop!=NULL)
              {
                  next_head = p_loop->next;//Saving the next command node
                  free(p_loop);//Free the curren node
                  p_loop = next_head;//setting p_loop to the next command node
              }
          }
          head = p->next;//making head a new node
          free(p);//free the curent node
          p=head;//setting p = next node
      }
    return head;//Returning head which is head in our case
}
/*---------------------------------------------------------------------------*/
void run_sender(Image *im, CmdNode *p, int *x, int *y,int *col,int *deli, char *position,char *direction)
{
    //This function sends commands to the drawLine function by taking the new position and direction from run function and changing the pointers of x and y
    
    //Adding all the values before hand
    int xadder = *(x)+p->val;//Adding the value of command to the x
    int yadder = *(y)+p->val;//Adding the value of command to the y
    int xsub = *(x)-p->val;//Subtracting the value of command from x
    int ysub = *(y)-p->val;//Subtracting the value of command from x
    
    //Getting rid of the all the bounds before hand
    if(xadder>=SIZEX){xadder = SIZEX-1;}//Making xadder = 511 if xadder>= 512
    if(yadder>=SIZEY){yadder = SIZEY-1;}//Making yadder = 511 if yadder>= 512
    if(xsub<0){xsub = 0;}//Making xsub = 0 if xsub < 0
    if(ysub<0){ysub = 0;}//Making ysub = 0 if ysub < 0
    
     //If the command is pendown then the Delimeter is 1
    if(strcmp("pendown",p->cmd)==0)
    {
        *(deli) = 1;
    }
    
    //If the command is penup then the Delimeter is 0
    if(strcmp("penup",p->cmd)==0)
    {
        *(deli) = 0;
    }
    
    //If the command is colour then change the Colour Value
    if(strcmp("colour",p->cmd)==0)
    {
        *(col) = p->val;
    }
    
    //Keeping Tract of the position change so I can change the directions
    if((strcmp("right",p->cmd)==0)||(strcmp("left",p->cmd)==0))
    {
        strcpy(position,p->cmd); //Change Position
        if (strcmp("E",direction)==0 && strcmp("right",position)==0)
        {
            //Going East and Making Right Turn means now position is South
            strcpy(direction, "S");
        }
        else if (strcmp("E",direction)==0 && strcmp("left",position)==0)
        {
            //Going East and Making Left Turn means now position is North
            strcpy(direction, "N");
        }
        else if (strcmp("S",direction)==0 && strcmp("right",position)==0)
        {
            //Going South and Making Right Turn means now position is West
            strcpy(direction, "W");
        }
        else if (strcmp("S",direction)==0 && strcmp("left",position)==0)
        {
            //Going South and Making Left Turn means now position is East
            strcpy(direction, "E");
        }
        else if (strcmp("W",direction)==0 && strcmp("right",position)==0)
        {
            //Going West and Making Right Turn means now position is North
            strcpy(direction, "N");
        }
        else if (strcmp("W",direction)==0 && strcmp("left",position)==0)
        {
            //Going West and Making Left Turn means now position is South
            strcpy(direction, "S");
        }
        else if (strcmp("N",direction)==0 && strcmp("right",position)==0)
        {
            //Going North and Making Right Turn means now position is East
            strcpy(direction, "E");
        }
        else if (strcmp("N",direction)==0 && strcmp("left",position)==0)
        {
            //Going North and Making Left Turn means now position is West
            strcpy(direction, "W");
        }
    }
    
    //Sending out the Commands to drawLine with the x and y Cordinates
    if(strcmp("E",(direction))==0 && strcmp("forward",p->cmd)==0)
    {
        if (*(deli) == 1)//1 = its pendown
        {
            drawLine(im,*(x),*(y),xadder,*(y),*(col));//Going East and Forward means x value will be added
        }
        *(x) = xadder;
    }
    else if(strcmp("W",(direction))==0 && strcmp("forward",p->cmd)==0)
    {
        if (*(deli) == 1)//1 = its pendown
        {
            drawLine(im,*(x),*(y),xsub,*(y),*(col));//Going West and Forward means x value will be subbed
        }
        *(x) = xsub;
    }
    else if(strcmp("N",(direction))==0 && strcmp("forward",p->cmd)==0)
    {
        if (*(deli) == 1)//1 = its pendown
        {
            drawLine(im,*(x),*(y),*(x),ysub,*(col));//Going North and Forward means y value will be subbed
        }
        *(y) = ysub;
    }
    else if(strcmp("S",(direction))==0 && strcmp("forward",p->cmd)==0)
    {
        if (*(deli) == 1)//1 = its pendown
        {
            drawLine(im,*(x),*(y),*(x),yadder,*(col));//Going South and Forward means y value will be added
        }
        *(y) = yadder;
    }
    if(strcmp("E",direction)==0 && strcmp("backward",p->cmd)==0)
    {
        if (*(deli) == 1)//1 = its pendown
        {
            drawLine(im,*(x),*(y),xsub,*(y),*(col));//Going East and Backward means x value will be subbed
        }
        *(x) = xsub;
    }
    else if(strcmp("W",direction)==0 && strcmp("backward",p->cmd)==0)
    {
        if (*(deli) == 1)//1 = its pendown
        {
            drawLine(im,*(x),*(y),xadder,*(y),*(col));//Going West and Backward means x value will be added
        }
        *(x) = xadder;
    }
    else if(strcmp("N",direction)==0 && strcmp("backward",p->cmd)==0)
    {
        if (*(deli) == 1)//1 = its pendown
        {
            drawLine(im,*(x),*(y),*(x),yadder,*(col));//Going North and Backward means y value will be added
        }
        *(y) = yadder;
    }
    else if(strcmp("S",direction)==0 && strcmp("backward",p->cmd)==0)
    {
        if (*(deli) == 1)//1 = its pendown
        {
            drawLine(im,*(x),*(y),*(x),ysub,*(col));//Going South and Backward means y value will be subbed
        }
        *(y) = ysub;
    }
}

/*---------------------------------------------------------------------------*/
void run(Image *im, CmdNode *head, int *endX, int *endY) {
  /**
   * This function runs the list of commands to move the turtle around and draw
   * the image, and returns the final position of the turtle in the variables
   * endX and endY.
   *
   * --------------------------------------------------------------------------
   *
   * NOTE: In the image we work with, the top-left pixel is (0,0),
   *       - x increases as you go right, up till SIZEX
   *       - y increases as you go down, up till SIZEY
   *
   *                 (0,0)                  (SIZEX, 0)
   *                   x------------------------x
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |   IMAGE         |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   x------------------------x
   *                (0, SIZEY)            (SIZEX, SIZEY)
   *
   * The image is in grayscale (black and white), so the colours are numbers
   * from [0-255] where 0 is black, 255 is white, and the values in between
   * are varying levels of gray.
   *
   * --------------------------------------------------------------------------
   *
   * Here's the setup - There is a turtle (with a pen) that walks along the
   * image. When the pen is down (on the paper), it draws a line along the path
   * that it walks on.
   *
   * The turtle initially starts at pixel (0, 0) [at the top left],
   * facing right (in the positive x direction). The pen starts off
   * as `down`, with the default colour being black (0).
   *
   * Here is what each command should do:
   *
   *  - penup          : Put the pen up (stop drawing)
   *  - pendown        : Put the pen down (start / continue drawing)
   *  - colour <val>   : Draw lines in colour <val> from now on
   *  - forward <val>  : Move the turtle forward <val> steps (pixels)
   *                     in the direction it is facing.
   *  - backward <val> : Same as above, except move backwards
   *  - right          : Turn the turtle to the right by 90 degrees
   *  - left           : Turn the turtle to the left by 90 degrees
   *
   * --------------------------------------------------------------------------
   *
   *      - a pointer to an image struct (use 'im')
   *      - (x,y) location of start point
   *      - (x,y) location of end point
   *      - a colour to draw the line in [0-255]
   */
    //Starting x and y Value  = 0
    int x = 0;
    int *x_p = &x;//Making a pointer for x value
    int y = 0;
    int *y_p = &y;//Making a pointer for y value
    CmdNode *p = NULL;
    p = head;//Saving the head to a p
    int col = 0;//Variable to Store the Colour of the Image
    int *col_p = &col; //Pointer to the Colour Variable
    int deli = 1;//Delimeter to if it is pendown or pendup
    int *deli_p = &deli;//Pointer to the pendown or pendup Variable
    char position[10] = "right";//Starting Poition of the Turtle is Right
    char direction[4] = "E";//Starting Direction of the Turtle is East
    while (p!=NULL)//While p is not Null
    {
        if (strcmp("loop",p->cmd)==0)//If the command is a Loop then we have to expore the nodes inside a Loop
        {
            for (int i=0; i<(p->val); i=i+1)//Counting number for times we have to loop through it
            {
                CmdNode *p_loop = NULL;
                p_loop = p->loop_head;//Saving the Loop Head
                while (p_loop!=NULL)//While it is not null
                {
                    run_sender(im,p_loop,x_p,y_p,col_p,deli_p,position,direction);//Send all the values to the run_sender
                    p_loop = p_loop->next;//keep going to next command in the loop
                }
            }
        }
        else //if it is not a loop means we only sending 1 time
        {
            run_sender(im,p,x_p,y_p,col_p,deli_p,position,direction);//Send all the values to the run_sender
        }
        p = p->next;//keep going to next node in the linked list
    }
    //Changing X and Y Values
    *(endX) = x;//Changing the values of the poiner to my x
    *(endY) = y;//Changing the values of the poiner to my y
    return;
}
/*---------------------------------------------------------------------------*/
// All done!
