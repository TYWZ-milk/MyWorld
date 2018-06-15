
---------------------------------------------
	configure file help

---------------------------------------------


The configure file is used for set

1. Limb Effect
2. Leaf mesh (.obj) and effect 
3. Leaf feature

Please Refer the Default configure <DefautTreeConfigure.ini>

[Limb]			

LimbEffectPath  	 = ..\\Resource\\Texture\\Limb.fx

[Leaf]

LeafEffectPath  	 = ..\\Resource\\Leaf\\leaf_02.fx
LeafMeshPath    	 = ..\\Resource\\Leaf\\leaf_02.obj


LeafDirectionX		 =  0.0
LeafDirectionY		 =  0.0
LeafDirectionZ		 =  1.0

LeafUpDirectionX	 =  0.0
LeafUpDirectionY	 =  1.0
LeafUpDirectionZ	 =  0.0

LeafScaleVectorX         = 0.05
LeafScaleVectorY         = 0.05
LeafScaleVectorZ         = 0.05

LeafPartten     	 = 1

LeafVerticalAngleStart 	 = 120
LeafVerticalAngleEnd 	 = 30

LeafHorizontalAngle	 = 180
LeafFrequence		 = 1

LeafFaceSunFactor        = 0.8

LeafCorrectDownAngle     = 0



"[Limb]"
	is limb Setction		

"LimbEffectPath  	 = ..\\Resource\\Texture\\Limb.fx"

	is limb effect path related to binary file


LeafDirectionX		 =  0.0
LeafDirectionY		 =  0.0
LeafDirectionZ		 =  1.0
	is Leaf main stem direction

LeafUpDirectionX	 =  0.0
LeafUpDirectionY	 =  1.0
LeafUpDirectionZ	 =  0.0
	is Leaf face direction

LeafScaleVectorX         = 0.05
LeafScaleVectorY         = 0.05
LeafScaleVectorZ         = 0.05
	is scale factor

LeafPartten     	 = 1
	is the birth in opposite at one point

LeafVerticalAngleStart 	 = 120
LeafVerticalAngleEnd 	 = 30
	is the start and end vertical angle on limb. the leaf between them is linear interpolated.

LeafHorizontalAngle	 = 180
	is horizontal rotate angle beteen neighbour leaf

LeafFrequence		 = 1
	is how much a limb has leaf

LeafFaceSunFactor        = 0.8
	is the leaf face sun factor 1.0 is the beggist , and 0 is smallest

LeafCorrectDownAngle     = 0
	is roate the down angle to some up.


NOTE:
IF not set , <DefautTreeConfigure.ini> will be used















