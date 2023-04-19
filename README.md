<h1 style="text-align:center">
    cub3D 
</h1>
<header>
    <h2>Summary</h2>
    <p>
        This project involves creating a small 3D game, using a graphics library called <a href="https://github.com/codam-coding-college/MLX42" target="_blank">miniLibX</a>. The game is a maze where the player moves around and can look in different directions, with walls and textures displayed in a 3D perspective.
    </p>
</header>


<main>
    <section>
        <h2>Instructions</h2>
        <p>
            This project has been developed under certain constraints and requirements, which include:
            <ol>
                <li>
                    Using miniLibX Graphics Library.
                </li>
                <li>
                    Setting the floor and ceiling colors to two different ones.
                </li>
                <li>
                    Displaying different wall textures that vary depending on which side the wall is facing (North, South, East, West).
                </li>
                <li>
                    Allowing smooth management of the window: changing to another window, minimizing, etc.
                </li>
                <li>
                    Allowing the user to use the keyboard to look left and right in the maze and to move the point of view through the maze.
                </li>
                <li>
                    Allowing the user to close the window and quit the program cleanly using either the ESC key or by clicking on the red cross on the window's frame.
                </li>
                <li>
                    Parsing a scene description file with the .cub extension, which includes a map composed of only six possible characters: 0 for an empty space, 1 for a wall, and N, S, E, or W for the player's start position and spawning orientation.
                </li>
            </ol>
        </p>
    </section>
    <section>
        <h2>Usage</h2>
        <p>
            To run the program, use the following command:
        </p>

```console
./cub3D <path/to/map.cub> 
```

Replace <path/to/map.cub> with the path to your scene description file with the .cub extension.
    </section>
    <section>
        <h2>Scene description file</h2>
        <p>
            The scene description file must follow specific rules and formats, including:
        </p>
        <ul>
            <li>
                A map composed of only six possible characters: 0 for an empty space, 1 for a wall, and N, S, E, or W for the player's start position and spawning orientation.
            </li>
            <li>
                The map must be closed/surrounded by walls, or the program must return an error.
            </li>
            <li>
                Each element in the file (except the map) must have a type identifier, followed by specific information for each object in a strict order.
            </li>
            <li>
                Each element (except the map) can be separated by one or more empty line(s).
            </li>
            <li>
                Each type of element can be set in any order in the file, except for the map which always has to be the last.
            </li>
            <li>
                Each type of information from an element can be separated by one or more space(s).
            </li>
        </ul>
    </section>
</main>

<p>
    Example of a valid scene:
</p>

```console
NO ./path_to_the_north_texture

SO ./path_to_the_south_texture

WE ./path_to_the_west_texture

EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0


1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
10010000000000000000000011111111
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111111111111111111111111
```

<footer>
        <section id="authors">
        <h2>Authors</h2>
        <p>
            CUB3D was created by <a href="https://github.com/UGOI" target="_blank">UGOI</a> and <a href="https://github.com/JideOgunlana" target="_blank">jide_O </a> as part of the 42 school curriculum.
        </p>
    </section>
</footer>
