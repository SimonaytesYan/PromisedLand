BUILDING_LOGIC(House,    ~((1 << 1) | (1 << 2) | (1 << 3)),  5, Resources( 0,  0, -15, 5,  5), Resources(-5, -5, 0, 0, 0), Resources(0, 0, 10, -5, -5))
BUILDING_LOGIC(Sawmill,  ~((1 << 0) | (1 << 1) | (1 << 3)), 20, Resources( 0,  0, -10, 0, -2), Resources( 0,  0, 2, 0, 0), Resources(0, 0,  7,  0,  2))
BUILDING_LOGIC(Well,     ~((1 << 1) | (1 << 2) | (1 << 3)),  2, Resources( 0,  0, -10, 0, -2), Resources( 0, 10, 0, 0, 0), Resources(0, 0,  7,  0,  2))
BUILDING_LOGIC(Windmill, ~((1 << 1) | (1 << 2) | (1 << 3)),  5, Resources( 0,  0, -10, 0, -2), Resources(10,  0, 0, 0, 0), Resources(0, 0,  7,  0,  2))
