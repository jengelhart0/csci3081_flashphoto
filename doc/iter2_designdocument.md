# Design Justifications for FlashPhoto
#### Group Name:
Something Filthy

#### Members:
- Joey Engelhart
- James Stanley

#### Instructions 
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.  
> A few tips to maximize the success of your design document:  
>   1. Make sure the **description** of your design decision only contains an objective description of how you structured your design and how it was implemented (specifically how your solution solves the problem given in the prompt). Save any arguments in favor of your design for the **justification** section.
>
>   2. Your justification will probably need to compare against at least one alternative, and you will need to provide a compelling argument for why your solution is better than the alternative.
>
>   3. Edit this file when writing your design document. Do not move or rename this file. Do not direct to any outside resources for your images or code. Place all images and code in this document. Please match the formatting of the [Example Design Document](https://github.umn.edu/umn-csci-3081F16/Example-Design-Document/blob/master/doc/DesignDocument.md) and [its source](https://raw.github.umn.edu/umn-csci-3081F16/Example-Design-Document/master/doc/DesignDocument.md?token=AAADyd5L8wd57F_qLX4Nf-2nVvfRlMj5ks5YH-qHwA%3D%3D) as precisely as possible, especially in regards to:
>     - **Formatting code** (do not include images of your code, make sure that your code is formatted with C++ coloring)
>     - **Inserting images**
>     - **Numbered lists for your tutorial**
>     - **Captioning your Figures**
>     - **Including the original prompts in their original quote form**  
> 
>  This formatting helps us grade your assignments effectively, and thus failure to meet these requirements may result in point deductions. Any material that is not presented in this design document will not be graded.
>   4. When including a class diagram, only show the classes and members that convey the point you're trying to make. For example, showing the class BaseGfxApp in a UML diagram will probably not be appropriate.





## 1  Design Question One
> This iteration of the project introduces the concept of filters. You had to implement several filters, which fell into two types: pixel-independent (where each pixel is filtered independently), and convolution-based (where filtering a pixel requires information about its neighboring pixels by means of a kernel). Naturally, a key design decision is how these filters are represented. Each filter has a different algorithm for modifying the canvas, and only some of these algorithms require kernels. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description

  To support implementations of both types of filters, we designed a simple filter inheritance structure. We created a base  `Filter` class, which provides data and functionality common to all filters. For example, every filter requires similar logic to `ApplyFilter()` to the canvas: 
  
###### Figure 1: Filter::ApplyFilter()
```c++
    int height = canvas_->height();
    int width = canvas_->width();
    int y, x;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            ModifyPixel(x, y);
        }
    }
```

  This logic in Figure 1 is used by all filters, regardless of type, because all must modify each pixel in the filter once in order to achieve the desired effect. However, specific filters must implement their own logic to `ModifyPixel()`s on the canvas (this is precisely what makes filters differ). The infrastructure for how to create a filter that extends from the base, abstract `Filter` class depends on which type: 

###### Figure 2: Filter Inheritance Hierarchy
![Filter UML](figures/filter_uml.png?raw=true)

####Pixel-independent Filters
  As Figure 2 illustrates, each pixel-independent filter extends a class directly from the base `Filter` class (e.g., the `Saturate` class for the saturation filter). Other than accessor and mutator methods, they only implement a `ModifyPixel()` function that modifies each target pixel independently from surrounding pixels according to the behavior defined for that filter in the requirements. 
  
####Convolution Filters
  Reading surrounding pixel values in order to modify any given pixel required a more complex inheritance structure than necessitated by the pixel-independent filters. We built a `ConvolutionFilter` class that extends `Filter` and implements additional data and functionality requirements. For example, unlike other filters, convolution filters must maintain a copy of the canvas so pixel modifications do not corrupt readings of surrounding pixels as we apply the filter to the canvas. 
  
  We implemented a `Kernel` class that defines a collection of values and methods for initializing these values that is used to read the appropriate target pixel and surrounding pixels as we apply convolution filters to the canvas. As Figure 2 depcits, for each convolution filter, we extended a specific kernel from the base `Kernel` class to represent the convolution behavior for that particular convolution filter (e.g., to implement a sharpen convolution filter, we created a `SharpenKernel` that extends `Kernel`). Therefore, for each convolution filter the requirements specified there is an associated instance of ConvolutionFilter that 'has a' specific subtype of `Kernel` associated with it. Because all behavior specific to a convolution filter is wrapped in its kernel, this meant we could otherwise treat every convolution filter the same. For example, one `ModifyPixel()` is used for every `ConvolutionFilter`, and a `weight(int x, int y)` function is used to read that `ConvolutionFilter`'s associated kernel at the correct coordinate in order to apply the logic specific to that filter. 

### 1.2 Design Justification

  In order to robustly implement convolution and pixel-independent filters, our design attempts to balance efficient development with maintainability and object-orientation. We went with a somewhat lightweight filter class hierarchy. We could have created a more verbose class structure in two ways: 1) we could have had a subclass for each type of ConvolutionFilter, each of which would have 'had a' kernel specific to that filter, and 2) we could have had a NonConvolutionFilter extending Filter, from which all of our non-convolution filters would have inherited. 
  
  The first alternative would have potentially simplified our namespacing and data access, as we could have more easily centralized some specificities of our kernel data and behavior in a specific filter class. The second would have given us a more 'balanced', symmetric inheritance tree. We instead chose the class relationship structure described above because it provided a number of advantages we deem more important. 
  
  First and foremost, it allows us to build out new filters more efficiently, because there is less class-building overhead for each new filter we want to create. Furthermore, we did not find evidence that an additional class layer for specific `ConvolutionFilter`s (e.g., a `MotionBlur` class) would have provided functional opportunities not afforded by our specific `Kernel` subclasses. We also determined that the possibility of using specific `ConvolutionFilter` subclasses, including only a single `Kernel`, and implementing all unique filter behavior and data in the inheriting `ConvolutionFilter` class would have limited us. The main limitation is that the filter behavior becomes harder to generalize and thus thwarts code reuse. 
  
###### Figure 3: Blur Tool UML
![Blur UML](figures/blur_uml.png?raw=true)

  As Figure 3 shows, the `Blur` tool utilizes a kernel with the same logic as the blur convolution filter. We were able to create a number of `BlurKernel`s for the `Blur` tool with our approach, whereas trading a `BlurFilter` for a `BlurKernel` would have likely meant rewriting the logic the blurring logic for the `Blur` tool. 

  While we tried to choose a design that is flexible to allow for future filter/tool developments with minimal wasted effort and refactoring, we acknowledge that choosing to forego specific ConvolutionFilter subclasses in favor of Kernel subclasses might limit the variety of convolution-based filters that are easily implementable in the future. If a proposed filter is different enough that it requires a different set of data members, we could have created more work for ourselves. This is a tradeoff we are willing to accept, given the number of advantages enumerated above.
  
  An additional challenge of `ConvolutionFilter`s posed by reading from surrounding pixels is how to handle edges. One option is to wrap around the canvas to the other side, however this often leaves strange discontinuities in the filter application. It is not uncommon for one side of an image, lacking any visual contiguity with the other, to have very different color data. Therefore we opted for a solution that 'reflects back' kernel overflow and underflow readings as illustrated below in Figure 4
  
###### Figure 4: Excerpt from ConvolutionFilter::ModifyPixel()
  
```c++
int i, j;
int edge_checked_i, edge_checked_j;
int kernel_x, kernel_y;

for (i = starting_y, kernel_y = 0; i <= ending_y; i++, kernel_y++) {
    // 'reflects' over/underflow values (e.g., i=-2 -> edge_checked_i=2)
    // i = canvas_width_ -> edge_checked_i = canvas_width-1)
    if (i >= 0 && i < canvas_height_) {
        edge_checked_i = i;
    } else {
        edge_checked_i = (canvas_height_
                       - (i % (canvas_height_ - 1)))
                       % canvas_height_;
    }
    for (j = starting_x, kernel_x = 0; j <= ending_x; j++, kernel_x++) {
        // see edge_checked_i note above
        if (j >= 0 && j < canvas_width_) {
            edge_checked_j = j;
        } else {
            edge_checked_j = (canvas_width_
                           - (j % (canvas_width_ - 1)))
                           % canvas_width_;
        }
    }
}  
```
  
  Notice that the edge_checked coordinates take kernel coordinates that have exceeded the canvas boundary and move them in the direction opposite to their overflow, by a magnitude equal to how much they exceeded the boundary by. While this means some canvas coordinates underneath the kernel are read twice, it makes it significantly more likely to avoid an outlier in color, and also avoids brightness loss.

## 2  Design Question Two
> One common software feature included in this iteration is the undo/redo mechanic, where any modification to the canvas can be reversed, and then optionally re-applied. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description
   Not part of the two-person group requirements.
### 2.2 Design Justification
   Not part of the two-person group requirements.

## 3  Design Question Three
> A new developer on your team must add a new filter to FlashPhoto. This filter is called  _Invert._ This filter performs the following conversion to all pixels in the canvas:
> ```
> newColor's red   = 1 - oldColor's red
> newColor's green = 1 - oldColor's green
> newColor's blue  = 1 - oldColor's blue
> ```
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new filter.

  The `Invert` filter would extend from the `Filter` base class and would require the same steps as any pixel-independent filter already implemented. The entirety of the inversion logic would be contained in the implementation of the pure virtual `ModifyPixel()` declared in filter.h. The steps are listed below:
  1. Create invert.h
    * Include the necessary headers for filters:
   ```c++
   #include "include/pixel_buffer.h"
   #include "include/filter.h"
   ```
    * Declare constructor that takes the canvas as an argument.
    * No `Invert`-specific data members will be required.
  2. Create invert.cc
    * Include invert.h
    * Define constructor, which simple calls the super constructor for `Filter`.
   ```c++
   Saturate::Saturate(PixelBuffer *canvas)
       : Filter(canvas) {}
   ```
    * Implement `ModifyPixel(int x, int y)`. Like all other filters, this would be called in each iteration through   `Filter::ApplyFilter()`. The most notable part of the logic gets the target pixel's current colors and inverts them. The following is a way to do so, having obtained a reference to the filter's   canvas_ member through `Filter::get_canvas()`:
   ```c++
   void Invert::ModifyPixel(int x, int y) {
      /* Get canvas */
      PixelBuffer* canvas = Filter::get_canvas();
      ColorData pixel = canvas->get_pixel(x, y);
      /* Create new color channel values */
      float red = 1 - pixel.red();
      float green = 1 - pixel.green()
      float blue = 1 - pixel.blue();
      /* Create new color */
      ColorData new_image(red, green, blue);
      canvas->set_pixel(x, y, new_image);
   }
   ```
  3. Hook the new filter in using filter_manager.cc. 
     * Add `FilterManager::ApplyInvert(PixelBuffer* canvas` to filter_manager.h
     * Implementation which involves creating an instance of the new filter and calling `ApplyFilter()` on it:
   ```c++
     void FilterManager::ApplyInvert(PixelBuffer* canvas) {
      std::cout << "Apply has been clicked for Invert" << std::endl;
      Invert filter(canvas);
       filter.ApplyFilter();
     }
   ```
  4. Add the new filter to the UI filter pane in flashphoto_app.cc



