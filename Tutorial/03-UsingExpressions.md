Defining and using expressions {#TutorialExpr}
================================

[TOC] 

The next step is to construct a function space over the mesh. The source code is
available in \c myexpression.cpp.

# Step by step explanations {#ex}

We start by loading a Mesh in 2D
\snippet myintegrals.cpp mesh

then we define some expression through the command line or config file: \c g is a scalar field and \c f is a vector field
\snippet myexpression.cpp expr

here is an example how to enter them, more are available below
```c++
feelpp_doc_myexpression --a=3 --functions.g="a*x*y:x:y:a" --functions.f="{sin(pi*x),cos(pi*y)}:x:y"
```

\remark You can print back the expression to the screen to check that everything is ok.
\remark You want to use as expression `a*x+b*y`, you have to define `a` and `b` as option (either in your code, either in the library).

then we compute the gradient of \c g and \c f
\snippet myexpression.cpp grad

Notice that template argument are given to \c grad to specify the shape of the
gradient: in the case of $$\nabla g$$ it is $$1\times2$$ and $$\nabla f$$
$$2\times 2$$ since we are in 2D.

then we compute the laplacian of \c g and \c f
\snippet myexpression.cpp laplacian

then we compute the divergence of \c f
\snippet myexpression.cpp div

and the curl of \c f
\snippet myexpression.cpp curl

Finally we evaluate these expression at one point given by the option \c x and \c y
\snippet myexpression.cpp eval

# Some results {#res}

We start with the following function $$g=1$$ and $$f=(1,1)$$.

```bash
shell> ./feelpp_doc_myexpression --functions.g=1:x:y --functions.f="{1,1}:x:y
g=1
f={x,-y}
grad(g)=[[0]]
grad(f)=[[1,0],[0,-1]]
laplacian(g)=[[0]]
laplacian(f)=[[0],[0]]
div(f)=[[0]]
curl(f)=[[0]]
Evaluation  at  (0,0):
           g(x,y)=1
           f(x,y)= 0
-0
Gradient:
     grad(g)(x,y)= 0 -0
     grad(f)(x,y)= 1  0
 0 -1
Divergence:
      div(f)(x,y)=0
Curl:
     curl(f)(x,y)=-3.14159
Laplacian:
laplacian(g)(x,y)=0
laplacian(f)(x,y)=0
0
```

The symbolic calculus system worked as expected.


# Complete code {#code}

The complete code reads as follows

\snippet myexpression.cpp all

to compile just use the `make` command in your compilation directory
```bash
make feelpp_doc_myexpression
```