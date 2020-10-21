var customMapFormat = {
    name = "Custom Text format",
    extension = "txt",
    read: function(fileName) {
        var file = new TextFile(fileName, TextFile.ReadOnly);
        var map = new TileMap();
        map.setSize(128, 128);
        map.setTileSize(16, 16);
        map.orientation = TileMap.Orthogonal;
        var tileset = tiled.open("C:/Dungeon Escape!/WORK/TileMap import/tileset.tsx");
        if(tileset && tileset.isTileset) {
            map.addTileset(tileset);
            var layer = new TileLayer();
            layer.width = map.width;
            layer.height = map.height;
            layer.name = "Import";
            var layerEdit = layer.edit();
            for (var i = 0; i < map.height; ++i) {
                var line = file.readLine();
                for (var c = 0; c < map.width; ++c) {
                    var tileID = parseInt(line.charAt(c), 10) - 1;
                    if(tileID >= 0) layerEdit.setTile( c, i, tileset.tile(tileID) );
                }
            }
            layerEdit.apply();
            map.addLayer(layer);
        }
        file.close();
        return map;
    }
}
tiled.registerMapFormat("Custom Text", customMapFormat);
