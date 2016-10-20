# Design Justifications for BrushWork
#### Group Name: **Something Filthy**
#### Members:
- Joey Engelhart
- James Stanley

#### Instructions 
> Respond to each of the design questions below.  Make your answers factual and compelling.  Where appropriate, reference alternative designs you considered, code snippets, and diagrams within your writing in order to be clear and back up your claims.  As we have discussed in class, when writing with reference to figures make sure to tell the reader what to look for in the diagram or what exactly you want the reader to notice in the code snippet.  Remember that the design of your project is worth 1/3 of the total project grade.  Also remember that when grading the design portion of the project, this design justification document is the only thing we will look at.  This document must stand on its own.  Rather than linking to your actual code, carefully pick the most important code snippets from your project to include here in order to provide convincing detail for your answers to the questions below.


## Design Question One
> This iteration of the project is all about tools. Naturally, a key design decision is how these tools are represented. Each tool has several characteristics, including the shape of the tool, its size, and the way it blends with the canvas when the tool is applied. Some tools share characteristics with other tools, such as how the pen and calligraphy pen tools blend with the canvas in the same manner. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge. We expect that you will include at least one figure showing the relationships of the classes affected by your design. Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 1.1 Design Description

With this iteration, we decided to develop a base `Tool` class that contained logic common to any tool that a user can select. For each of those tools, we implemented a specific subclass (e.g., `CaligraphyPen`) that inherited from the base `Tool` class and provided logic specific to that tool. The base class methods provided functionality that did not need to be rewritten for every extending subtool. For example, because every tool has a mask which is represented similarly (i.e., with the same data structure) but differs in shape and intensity values, we implemented a `CalculateMask()` method for each derived class that uses `Tool::mask()` to set that particular mask to that tool. 

Additionally, we provided the basic draw logic in `Tool` through `Tool::Draw()` as every subtool is drawn the same way: it uses the provided x-y coordinates and the mask values for that tool to set each pixel within the mask’s coverage to the appropriate current color and intensity. 

If a tool required draw logic dissimilar to that implemented in the base class, we could override `Draw()` method in that subclass. This occurred for tools whose application to the canvas necessitated factoring in the background color in some proportion. This only applied in two cases:

 1. `Highlighter` so we could consider the canvas' luminance when blending colors. This unfortunately required reusing the code from `Tool::Draw()`, but we chose to do so in order to make highlighter appear more natural.
 2. `Eraser` whose implementation serves as an adapter to its parent class' implementation. This will be described in further details below.

### 1.2 Design Justification

We initially considered an alternative tool design that utilized only one class, a DrawingTool class. This class would include the same shared logic as the Tool base class we ultimately developed, encapsulating all draw and mask-setting functionality. Our justification for this design was that each tool only differed from the others in its mask: the shape and intensity of any pixel within the mask structure could entirely determine its appearance on the canvas. All application of the tool was the same among different tools. This would have allowed us to keep a smaller set of classes.

Ultimately, we rejected this alternative in favor of implementing each new tool as a subclass of our base `Tool` class. Although this means we have more classes to keep track of, it allows significantly more flexibility for future development. For example, it makes it easier to design idiomatic tools in the future, with more complex behavior that may not be shared by existing tools. 

With our original design, implementing logic like this would be extremely difficult, if not impossible in some cases. It would allow for no encapsulated space to keep such logic organized, and would require convoluted control structures floating freely in functions designed to provide shared functionality. Because of the high likelihood that we will need more tools in future iterations, and the behavior is likely to build in complexity rather than become simpler, building out a foundation of supportive but simple inheriting classes extending from a shared base class will help our implementation be more flexible and powerful as we continue to develop it. 


## Design Question Two
> Unlike most of the tools, the Eraser returns the canvas to its original color. One of the challenges in this iteration is giving the eraser the authority or information required to have this effect while having minimal impact on the way the rest of the tools are defined. 
> First, in the **Design Description** section below, describe the design you developed to address this challenge.  Second, in the **Design Justification** section below present the most compelling argument you can for why this design is justified.  Note that our expectation is that you will need to discuss the pros (and maybe cons) of your final design as compared to alternative designs that you discussed in your group in order to make a strong case for justifying your design.

### 2.1 Design Description

We did this by having `BrushWorkApp` pass its pointer `PixelBuffer display_buffer_` to `Tool::Draw()`. This allowed the tool to apply itself directly to the canvas which it is passed. Most importantly, this allows `Tool::Draw()` to access the background color through use of `PixelBuffer::background_color()`. As illustrated in the code block below, `Eraser` does implement its own `Draw()` function, but it serves as an adapter to `Tool::Draw()` which is called with the original canvas color rather than the color it is passed. 
```c++
void Eraser::Draw(int x, int y, 
    float red, float green, float blue, PixelBuffer* display) {
    // Get current background color
    ColorData original_color = display->background_color();
    // Call parent method with background color instead of tool color
    Tool::Draw(x, y,
        original_color.red(), original_color.green(), original_color.blue(),
        display);
}

```

### 2.2 Design Justification

We chose this design for a variety of reasons. Primarily, it allows the flexibility to alter a `PixelBuffer` that isn't the canvas. While this isn't a requirement at the moment, future iterations could introduce the need for tools to edit multiple objects. Furthermore, by passing the current display_buffer_ to a given `Tool`, we can access the current background color as opposed to storing it as a variable in each tool should we desire the flexibility to change background color. 

Our original design involved passing a `PixelBuffer` to each `Tool` as part of its constructor; however, for the reasons outlined above, we chose to pass the `PixelBuffer` to `Tool::Draw()` which affords additional flexibility. From an object-oriented perspective, it's logical for a real-world tool to exist independent of its canvas, so we allowed the instantiation of a `Tool` without this restriction.

Using `Eraser::Draw()` as an adapter for its parent class prevents any additional logic in `BrushWorkApp` that might need to check for the current tool. Lastly, it allowed us to reuse the code in `Tool::Draw` with the very simple and concise implementation of `Eraser::Draw()` shown in Section 2.1.


## Design Question Three
> A new developer on your team must add a new tool to BrushWork. This tool is called  _Pencil._ This tool is a single, non-transparent pixel that completely replaces the existing colors on the canvas in the same way as the pen or calligraphy pen blend.  
> Describe in the form of a tutorial (including code snippets) exactly what changes would need to be made to your program in order to fully integrate this new tool.

### Programming Tutorial: Adding a New Pencil Tool to BrushWork

1. Add a new header file (include/pencil.h) with declarations of its constructor, destructor, and `CalculateMask()`.
2. Add source file (src/pencil.cc) for a Pencil tool, which inherits Tool. 
3. When creating this new class, construct its mask as a float[] of size 1, whose single intensity value is set equal to 1.0. For example, its constructor would look like:

        Pencil::Pencil(void) : Tool(1, 1( {
            CalculateMask();
        }
        
 Because it can reuse `Tool::Draw()`, the only other method to implement is `CalculateMask()`:

        Pencil::CalculateMask(void) {
            float[1] new_mask = {1.0};
            Tool::mask(new_mask);
        }

4. In the section of brushwork_app.cc following the comment `“// create new interface buttons for different tools,”` add a new radio button with the code line: 

 `new GLUIRadioButton(radio, “Pencil”);`

 Note the ordinal position at which you include this new line, and how it changes the ordinal position for the existing buttons. For example, if there are 5 tools before you add Pencil, and you place Pencil after Pen (i.e., the first tool in the series of statements), Pencil will be tool 1 (i.e., the 2nd tool) and the tools which follow Pencil will need to have their switch case incremented by one in the next step.
 
5. Add Pencil to the switch statement in `BrushWorkApp::ChangeTool()`. Assign it a case that matches the ordinal position mentioned in step 3. Update cases of tools whose position changed in step 3. Assuming this tool's radio button is added beneath our other tools, the switch statement in `BrushWorkApp::ChangeTool()` will look like this:

        switch (current_tool) {
            case 0:
                new_tool = new Pen();
                break;
            case 1:
                new_tool = new Eraser();
                break;
            case 2:
                new_tool = new SprayCan();
                break;
            case 3:
                new_tool = new CaligraphyPen();
                break;
            case 4:
                new_tool = new Highlighter();
                break;
            case 5:
                new_tool = new WireBrush();
                break;
            case 6:
                new_tool = new Pencil();
                break;
        }

6. Add `#include include/pencil.h` in brushwork_app.cc.
