/**
 * Created by deii66 on 2018/3/15.
 */
//把创建鼠标跟随几何图形和实体图形都抽象成函数，通过点击事件进行调用
function cubeBuild(cube){
    cubefollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.BoxGeometry( 50, 50, 50 );
    if(cube=="brick")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/brick.png" ) } );
    else if(cube=="bookshelf")
        cubeMaterial = new THREE.MeshLambertMaterial( { map: new THREE.TextureLoader().load( "textures/blocks/bookshelf.png" ) } );
    else if(cube=="stonewall")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/stone-wall.jpg" ) } );
}
function planeBuild(plane){
    planefollow();
    // 实体对象，就是鼠标点击确定之后的实体对象，并且实体对象的图片引入
    cubeGeo = new THREE.BoxGeometry( 50, 10, 50 );
    if(plane=="water")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/water_flow.png" ) } );
    else if(plane=="woodfloor")
        cubeMaterial = new THREE.MeshLambertMaterial( {  map: new THREE.TextureLoader().load( "textures/blocks/wood-floor.jpg" ) } );
    for(var i=0; i <cubeGeo.vertices.length;i++){
        cubeGeo.vertices[i].y = -20;
    }

}
function cubefollow(){
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
function planefollow(){
    scene.remove(rollOverMesh);
    // 这个几何对象是鼠标在移动时候，跟随鼠标显示的几何对象
    rollOverGeo = new THREE.BoxGeometry( 50, 10, 50 );//创建一个盒状几何对象
    rollOverMaterial = new THREE.MeshBasicMaterial( { color: 0xff0000, opacity: 0.5, transparent: true } );
    for(var i=0; i <rollOverGeo.vertices.length;i++){
        rollOverGeo.vertices[i].y = -20;
    }
    //创建一个色彩为红色的材料，透明度为半透明
    rollOverMesh = new THREE.Mesh( rollOverGeo, rollOverMaterial );
    //通过mesh方法把颜色应用到几何对象上
    scene.add( rollOverMesh );
    //最后把该立方体对象添加到场景scene中
}