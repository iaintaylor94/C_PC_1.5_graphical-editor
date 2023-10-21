# Programming Challenges
## Problem 1.5: Graphical Editor[^1]

### Problem description
This problem creates an array of characters which represents a bitmap of colours. Then, based on formatted input, it processes this array - changing the content of this array. Once the program finishes editing the array, the contents (along with the name of the input) are printed to the display.


### Example 
> **Input**                 
> I 5 6     
> L 2 3 A         
> S one.bmp     
> G 2 3 J  
> F 3 3 J   
> V 2 3 4 W      
> H 3 2 4 Z       
> S two.bmp
> X        

>**Output**          
>one.bmp     
>00000         
>00000          
>0A000           
>00000      
>00000
>00000           
>two.bmp             
>JJJJJ          
>JJZZJ
>JWJJJ
>JWJJJ
>JJJJJ
>JJJJJ


[^1]: Programming Challenges By S.Skienna and M.Revilla, page 19