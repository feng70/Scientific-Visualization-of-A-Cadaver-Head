# Scientific-Visualization-of-A-Cadaver-Head
In this assignment,I made a scientific visualization of a cadaver head using vtk(**[Visualization ToolKit](http://www.vtk.org/)**).

## Data: ##
The dataset comes from **[The stanford Volume Data Archive](http://graphics.stanford.edu/data/voldata/)**. 

Here is the info of the original cthead data:

    Description: 	CT study of a cadaver head
	Dimensions:		113 slices of 256 x 256 pixels,
					voxel grid is rectangular, and
					X:Y:Z aspect ratio of each voxel is 1:1:2
	Files:			113 binary files, one file per slice
	File format:    16-bit integers (Mac byte ordering), file contains no header
	Data source:    acquired on a General Electric CT Scanner and provided
                	courtesy of North Carolina Memorial Hospital

I used the 16-bit TIF format data which reformatted from above. 

## Algorithm: ##
The main algorithm of the rendering is **[Marching cubes](https://en.wikipedia.org/wiki/Marching_cubes)**.

Marching cubes algorithm use for extracting a polygonal mesh of an isosurface from a three-dimensional discrete scalar field (sometimes called voxels). The algorithm proceeds through the scalar field, taking eight neighbor locations at a time (thus forming an imaginary cube), then determining the polygon(s) needed to represent the part of the isosurface that passes through this cube. The individual polygons are then fused into the desired surface.The applications of this algorithm are mainly concerned with medical visualizations such as CT and MRI scan data images, and special effects or 3-D modelling with what is usually called metaballs or other metasurfaces(wiki).

![](https://github.com/ruange/Scientific-Visualization-of-A-Cadaver-Head/blob/master/image%20and%20gif/MarchingCubes.png)

## Display: ##
There are two surfaces rendered,representing skin and bone.The opacity of the surface is adjustable.

Set skin opacity 1:

![](https://github.com/ruange/Scientific-Visualization-of-A-Cadaver-Head/blob/master/image%20and%20gif/opacity_1.gif)

Set skin opacity 0.5:

![](https://github.com/ruange/Scientific-Visualization-of-A-Cadaver-Head/blob/master/image%20and%20gif/opacity_0.5.gif)

set skin opacity 0:
 
![](https://github.com/ruange/Scientific-Visualization-of-A-Cadaver-Head/blob/master/image%20and%20gif/opacity_0.gif)