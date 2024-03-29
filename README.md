Copyright 2021 - 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)

## -MAIN-

- We initialize the picture with 0 for the double variables and with NULL for the matrix
- We read what's given from stdin line by line, using fgets
- We stop when we reach the EXIT command
- From the line that was read earlier we should determine the operation's keyword
- After doing so, what remains in the input should be everything else beside the operation
- We'll also be careful about memory allocation errors, which will be solved accordingly in each function; mem_ups represents a flag for such situations
-------------------------------------------------------------------------------

## -LOAD-

- We determine the file that should be opened for reading
- We open it in the binary mode, since we can also use fscanf to read the ascii content from it
- If we already have a matrix in the memory, we get rid off it
- We determine image's type, its number of columns and its number of rows
- Reading the comments and ignoring them
- If the picture is not black and white we also read its maximum intensity
- Dinamically allocating space for the new image
- Now, we can read the matrix
- The last step is to select it all
-------------------------------------------------------------------------------

## -SELECT-

- Firstly, it should be checked whether the select is meant for the entire matrix
- If so, we set the coordinates accordingly
- We'll then check if the input has enough int values for a select operation
- Now, we read the values for the selection
- We determine the smallest value for each range (x1, x2, y1, y2)
- If the values are valid, we set the image as per usual
-------------------------------------------------------------------------------

## -ROTATE-

- After dealing with the situation where we don't have any matrix loaded, we check if there is only one argument to the operation
- Also checking if the angle is valid (is part of the array of numbers that can be divided by 90)
- For certain cases, the rotation is not needed: +/-360, 0
- Angle is now with 360 bigger, as we want to take into consideration the negative numbers too
- We apply the rotation algorithm in 2 ways:
    - one for when the matrix is fully selected, (so the dimensions might not be equal)
        - we swap its dimensions at every rotation we make
        - and we send 1 to the rotate_clockwise function
    - one for when the selection is square
        - changing the dimensions at every iteration is not required anymore
        - we send 0 to the rotate_clockwise function
- We now print the success message, along with the angle, from which we substract the 360 added earlier
-------------------------------------------------------------------------------

## -CROP-

- The cropping mechanism is based on a temporary matrix which stores the smaller, resulting crop
- When done with transfering the elements, we deallocate the previous matrix
- We put the values back into our structure
- We set the new values for the number of rows and columns
-------------------------------------------------------------------------------

## -APPLY-

- After considering all the error inducing possibilities, we go on to apply every filter in its own separate function
- For every such function, we defined the kernel for the filter
- We applied the filter if the image was coloured
    - We used a temporary matrix to store the result of the APPLY
    - If the selection contains one of the matrix's margins, we don't apply the filter on that part
    - In order to do so, we add 1 to the starting value, and substract 1 from the last value in the interval (x1, x2 and y1, y2)
    - For every pixel of colour we'll have a sum which memorizes the partial result
    - Lastly, tmp gets the sum, after it went through the clamp function
    - By doing so, we avoid the overflow
    - To be noted: the round function we'll be applied right before saving, so we'll be more precise in our calculations
    - The initial image gets now the new, filtered picture
    - Freeing the temporary matrix is a must
-------------------------------------------------------------------------------

## -SAVE-

- Using sscanf, we read the file name in which we'll write the image
- We crop the name from the input
- If there's anything left there, we check if it's the "ascii" magic word
- We now open the file in binary write mode, as we can use both fprintf and fwrite to write stuff in it
- We write the info about the picture, and depending on the "ascii" magic word, the matrix, with fprintf or with fwrite
-------------------------------------------------------------------------------

## -EXIT-

- We exit the "image editor", we deallocate all the dinamically allocated resources, we stop reading commands from stdin
-------------------------------------------------------------------------------