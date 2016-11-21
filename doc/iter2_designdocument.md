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

~~~~
    int height = canvas_->height();
    int width = canvas_->width();
    int y, x;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            ModifyPixel(x, y);
        }
    }
~~~~

  This logic is used by all filters, regardless of type, because all must modify each pixel in the filter once in order to achieve the desired effect. However, specific filters must implement their own logic to `ModifyPixel()`s on the canvas (this is precisely what makes filters differ). The infrastructure for how to create a filter that extends from the base, abstract `Filter` class depends on which type: 

####Pixel-independent Filters
  Each pixel-independent filter extended a class directly from the base `Filter` class (e.g., the `Saturate` class for the saturation filter). They implement a `ModifyPixel()` function that modifies each target pixel independently from surrounding pixels, according to the behavior defined for that filter in the requirements. 
  
####Convolution Filters
  Reading surrounding pixel values in order to modify any given pixel required a more complex inheritance structure than necessitated by the pixel-independent filters. We built a `ConvolutionFilter` class that extends `Filter` and implements additional data and functionality requirements. For example, unlike other filters, convolution filters must maintain a copy of the canvas so pixel modifications do not corrupt readings of surrounding pixels as we apply the filter to the canvas. 
  
  We implemented a `Kernel` class that defines a collection of values and methods for initializing these values that is used to read the appropriate target pixel and surrounding pixels as we apply convolution filters to the canvas. For each convolution filter, we extended a specific kernel from the base `Kernel` class to represent the convolution behavior for that particular convolution filter (e.g., to implement a sharpen convolution filter, we created a `SharpenKernel` that extends `Kernel`). Therefore, each convolution filter the requirements entailed has an associated instance of ConvolutionFilter that 'has a' specific subtype of `Kernel` associated with it. Because all behavior specific to a convolution filter is wrapped in its kernel, this meant we could otherwise treat every convolution filter the same. For example, one `ModifyPixel()` is used for every `ConvolutionFilter`, and a `weight(int x, int y)` function is used to read that `ConvolutionFilter`'s associated kernel at the correct coordinate in order to apply the logic specific to that filter. 

### 1.2 Design Justification

In order to robustly implement convolution and pixel-independent filters, our design attempts to balance efficient development with maintainability and object-orientation. 

## 2  Design Question Two
> One common software feature included in this iteration is the undo/redo mechanic, where any modification to the canvas can be reversed, and then optionally re-applied. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description

### 2.2 Design Justification


## 3  Design Question Three
> A new developer on your team must add a new filter to FlashPhoto. This filter is called  _Invert._ This filter performs the following conversion to all pixels in the canvas:
> ```
> newColor's red   = 1 - oldColor's red
> newColor's green = 1 - oldColor's green
> newColor's blue  = 1 - oldColor's blue
> ```
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new filter.
