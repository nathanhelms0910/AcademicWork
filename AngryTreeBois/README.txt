Project Members: Trenton Taylor, Morgan Magner, Nathan Helms, Andrew Jones
Project Version: 1.0.5 (final) 
Date: 10/2/2020
Dr. Marmorstein

To Compile: 
  Type qmake, and then type make.

To Run:
  Type ./AngryTreeBois


Program Instructions:
  This program gives the user various tools are their disposal to manipulate
  transform images.

     $ Saving and Loading Images:

      * Under file menu at the top left allows the user to save and load images.

        By clicking load, you can load in an image file (.png or .jpg).

        By clicking save, you can save an image file with a specified name.
        Note: Make sure you include the desired file type (file.png or file.jpg)

     $ Modify Images:

      * On the toolbar to the right of the screen

        - The select tool simply does nothing, please feel free to use it as much
          as you want.

        - The remove color tool can be used to click and remove a color from the 
          image.

        - The swap tool will replace a color in the image with the one the user
          selects.

        - The color count tool will display every color that exists in the image.
          Note: Images with a large amount of colors may cause the color count tool's
          display window to go past the edge of the screen.
	
	- The border tool will add a black border of 1 px. in width to your image. 
	  All you have to do is select the button then click on the image. Every
	  time you load a new image, you should be able to add the border again.
	  
	  WARNING: if you swap colors, there is a high possibility that the new
	  color will cover over the border. I would recommend swapping colors 
	  FIRST, then adding the border

  Details:

   $ AngryTreeBois is a graphical program that allows a user to load, save, and
     modify different images (png and jpg). The user is able load images, save images,
     remove colors from images, change image borders, swap different colors, and and view 
     the number different colors an image contains. 


  Specific Program Details:

   $ This program uses an AVL tree to represent an image. This AVL tree consists of
     several functions such as insert, find, and remove that allow the tree to be
     created, accessed, and changed. The tree also contains several rotation functions
     that are used to keep it "balanced" according to the AVL and Binary tree properties.

  Testing:
    
    CAUTION: Images in the HARD, VERY HARD, or ARMAGEDDON folders may cause the program to run slow.

    $ There are several pre-loaded images in this directory that you can use to test 
      the program. These are located within the "tests" directory. Each test is labeled 
      with a difficulty tag such as "Easy, Medium, Hard." These denote the stress each 
      test will put on your machine. Please feel free to use these as a general way to test
      the program.

Important Notes:

    CAUTION: Big images will cause certain actions such as loading and removing colors 
             to put heavy stress on your machine, please use caution when attempting to 
             load or modify a large image. (Large images like (800 x 80) or (1920 x 1080))
