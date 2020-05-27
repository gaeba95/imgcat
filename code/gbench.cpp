/* 06.05.2020 - Sydney Hauke - HPC - REDS - HEIG-VD */

#include <benchmark/benchmark.h>

extern "C" {
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include "environment.h"
    #include "convert.h"
    #include "imgcat.c"
}

class IFSFixture : public benchmark::Fixture {
public:
    void SetUp(const ::benchmark::State& state)
    {
        print_width = get_terminal_width();
        imgfile = fopen("images/stars.png", "rb");
        if (!imgfile) {
          fprintf(stderr, "Failed to open image file.\n");
          exit(1);
        }
        raster = create_raster_from_png(imgfile);

        if (!raster) {
            fprintf(stderr, "Failed to get pixel data from file.\n");
            exit(1);
        }
    }

    void TearDown(const ::benchmark::State&)
    {
        fclose(imgfile);
        free_raster(raster);
    }

protected:
    FILE* imgfile;
    raster_t *raster;
    int print_width;
};

BENCHMARK_DEFINE_F(IFSFixture, print_raster_test)(benchmark::State& state)
{
    while (state.KeepRunning()) {
        print_raster(raster, print_width);
    }
}

BENCHMARK_REGISTER_F(IFSFixture, print_raster_test)
    ->Unit(::benchmark::kMicrosecond);
    

BENCHMARK_MAIN();
