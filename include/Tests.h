#pragma once
#include <Maze.h>
#include <Config.h>
#include <MazeDraiver.h>
#include <Solver.h>
#include <Navigator.h>
#include <Router.h>
void tests_maze()
{
    maze_set_wall(Vec2{0,0},Maze::CellWalls{Maze::WALL,Maze::WALL,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{1,0},Maze::CellWalls{Maze::OPEN,Maze::OPEN,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{2,0},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{3,0},Maze::CellWalls{Maze::OPEN,Maze::OPEN,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{4,0},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::WALL,Maze::WALL});

  maze_set_wall(Vec2{0,1},Maze::CellWalls{Maze::WALL,Maze::WALL,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{1,1},Maze::CellWalls{Maze::OPEN,Maze::OPEN,Maze::OPEN,Maze::OPEN});
  maze_set_wall(Vec2{2,1},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{3,1},Maze::CellWalls{Maze::OPEN,Maze::OPEN,Maze::OPEN,Maze::OPEN});
  maze_set_wall(Vec2{4,1},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::WALL,Maze::WALL});

  maze_set_wall(Vec2{0,2},Maze::CellWalls{Maze::WALL,Maze::WALL,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{1,2},Maze::CellWalls{Maze::OPEN,Maze::OPEN,Maze::OPEN,Maze::OPEN});
  maze_set_wall(Vec2{2,2},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{3,2},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::OPEN,Maze::OPEN});
  maze_set_wall(Vec2{4,2},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::WALL,Maze::WALL});

  maze_set_wall(Vec2{0,3},Maze::CellWalls{Maze::WALL,Maze::WALL,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{1,3},Maze::CellWalls{Maze::OPEN,Maze::OPEN,Maze::OPEN,Maze::OPEN});
  maze_set_wall(Vec2{2,3},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::WALL,Maze::WALL});
  maze_set_wall(Vec2{3,3},Maze::CellWalls{Maze::WALL,Maze::OPEN,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{4,3},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::WALL,Maze::WALL});

  maze_set_wall(Vec2{0,4},Maze::CellWalls{Maze::WALL,Maze::WALL,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{1,4},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::OPEN,Maze::OPEN});
  maze_set_wall(Vec2{2,4},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::WALL,Maze::OPEN});
  maze_set_wall(Vec2{3,4},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::OPEN,Maze::OPEN});
  maze_set_wall(Vec2{4,4},Maze::CellWalls{Maze::OPEN,Maze::WALL,Maze::WALL,Maze::WALL});
  //maze_set_wall(Vec2{,},Maze::CellWalls{Maze::,Maze::,Maze::,Maze::});
  Serial.println();
  draw_maze(MAZE_WIDTH, MAZE_HEIGHT);

  uint32_t time0 = micros();
  solver_init();
  solver_set_start_goal(Vec2 {0,0}, Vec2 {4,3});
  uint32_t time1 = micros();

  draw_maze_with_solver( MAZE_WIDTH, MAZE_HEIGHT);

  Serial.print("init solve: ");
  Serial.print(time1-time0);
  Serial.println("us ");

  bool solved = false;
  do
  {
    uint32_t time0s = micros();
    solved = solver_solve();
    uint32_t time1s = micros();
    Serial.print("solving solve: ");
    Serial.print(time1s-time0s);
    Serial.println("us ");
  } while (!solved);

  draw_maze_with_solver( MAZE_WIDTH, MAZE_HEIGHT);
  
}

void test_nav_print_coords()
{
    Serial.print("x: ");
    Serial.print(nav_get_x());
    Serial.print(" y: ");
    Serial.print(nav_get_y());
    Serial.print(" sigma: ");
    Serial.println(nav_get_sigma());
}

void test_navigator()
{
    nav_init();
    test_nav_print_coords();
    nav_tick(0,0,0);
    test_nav_print_coords();

    nav_tick(2,-2,2);
    test_nav_print_coords();
    nav_tick(2,-2,2);
    test_nav_print_coords();
    nav_tick(2,-2,2);
    test_nav_print_coords();
    nav_tick(2,-2,2);
    test_nav_print_coords();
}

void test_router()
{
  tests_maze();
  nav_init();
  router_init();
  router_tick();
  Serial.println("Router path: ");
  Serial.println(router_path_buffer);

  router_path_to_cyc(router_path_buffer);
  Serial.println("router cyc:");
  for (size_t i =0; i<router_cyc_index;i++)
  {
    Serial.print(router_cyc_buffer[i].raw,BIN);
    Serial.println("");
  }
  Serial.println();
  for (size_t i =0; i<router_cyc_index;i++)
  {
    asmr_prog_buffer[i]=router_cyc_buffer[i];
  }
}