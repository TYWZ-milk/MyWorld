/**
 * Created by deii66 on 2018/3/15.
 */
//把创建鼠标跟随几何图形和实体图形都抽象成函数，通过点击事件进行调用
function cubeBuild(cube){
    cubeFollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.BoxGeometry( 50, 50, 50 );
    if(cube=="brick")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/brick.png" ) } );
    else if(cube=="bookshelf")
        cubeMaterial = new THREE.MeshLambertMaterial( { map: new THREE.TextureLoader().load( "textures/blocks/bookshelf.png" ) } );
    else if(cube=="stonewall")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/stone-wall.jpg" ) } );
    else if(cube=="mossywall")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/cobblestone_mossy.png" ) } );
}
function planeBuild(plane){
    planeFollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.BoxGeometry( 50, 10, 50 );
    if(plane=="water")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/water_flow.png" ) } );
    else if(plane=="woodfloor")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/wood-floor.jpg" ) } );
    else if(plane=="clay")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/clay.png" ) } );
    else if(plane=="cobblestone")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/cobblestone.png" ) } );
    else if(plane=="dirt")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/dirt.png" ) } );
    for(var i=0; i <cubeGeo.vertices.length;i++){
        cubeGeo.vertices[i].y = -23;
    }

}
function upplaneBuild(upplane){
    upplaneFollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.BoxGeometry( 1, 50, 50 );
    if(upplane=="daywindow")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/daylight_detector_top.png" ) } );
    else if(upplane=="irondoor")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/door_iron_upper.png" ) } );

}
function cylinderBuild(scylinder){
    cylinderFollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.CylinderBufferGeometry( 10,10, 10, 18 ,3);
    if(scylinder=="cake")
        cubeMaterial = new THREE.MeshLambertMaterial( { map: new THREE.TextureLoader().load( "textures/square-outline-textured.png" ) } );
    cubeGeo.position.y=-30;
}
function cubeFollow(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.BoxGeometry( 50, 50, 50 );//创建一个盒状几何对象
    rollOverMaterial = new THREE.MeshBasicMaterial( { color: 0xff0000, opacity: 0.5, transparent: true } );
    //创建一个色彩为红色的材料，透明度为半透明
    rollOverMesh = new THREE.Mesh( rollOverGeo, rollOverMaterial );
    //通过mesh方法把颜色应用到几何对象上
    scene.add( rollOverMesh );
    //最后把该立方体对象添加到场景scene中
}
function planeFollow(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.BoxGeometry( 50, 10, 50 );//创建一个盒状几何对象
    rollOverMaterial = new THREE.MeshBasicMaterial( { color: 0xff0000, opacity: 0.5, transparent: true } );
    for(var i=0; i <rollOverGeo.vertices.length;i++){
        rollOverGeo.vertices[i].y = -23;
    }
    //创建一个色彩为红色的材料，透明度为半透明
    rollOverMesh = new THREE.Mesh( rollOverGeo, rollOverMaterial );
    //通过mesh方法把颜色应用到几何对象上
    scene.add( rollOverMesh );
    //最后把该立方体对象添加到场景scene中
}
function cylinderFollow(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.CylinderGeometry( 10,10, 10, 18 ,3 );//创建一个盒状几何对象
    rollOverMaterial = new THREE.MeshBasicMaterial( { color: 0xff0000, opacity: 0.5, transparent: true } );

    //创建一个色彩为红色的材料，透明度为半透明
    rollOverMesh = new THREE.Mesh( rollOverGeo, rollOverMaterial );
    //通过mesh方法把颜色应用到几何对象上
    scene.add( rollOverMesh );
    //最后把该立方体对象添加到场景scene中
}
function upplaneFollow(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.BoxGeometry( 10, 50, 50 );//创建一个盒状几何对象
    rollOverMaterial = new THREE.MeshBasicMaterial( { color: 0xff0000, opacity: 0.5, transparent: true } );

    //创建一个色彩为红色的材料，透明度为半透明
    rollOverMesh = new THREE.Mesh( rollOverGeo, rollOverMaterial );
    //通过mesh方法把颜色应用到几何对象上
    scene.add( rollOverMesh );
    //最后把该立方体对象添加到场景scene中
}
