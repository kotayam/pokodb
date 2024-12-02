cmd_Release/pokodb.node := ln -f "Release/obj.target/pokodb.node" "Release/pokodb.node" 2>/dev/null || (rm -rf "Release/pokodb.node" && cp -af "Release/obj.target/pokodb.node" "Release/pokodb.node")
