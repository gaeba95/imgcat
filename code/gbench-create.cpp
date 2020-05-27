/* 06.05.2020 - Sydney Hauke - HPC - REDS - HEIG-VD */

#include <benchmark/benchmark.h>

extern "C" {
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include "environment.h"
    #include "convert.h"
}

class IFSFixture : public benchmark::Fixture {
public:
    void SetUp(const ::benchmark::State& state)
    {
        imgfile = fopen("images/stars.png", "rb");
        if (!imgfile) {
          fprintf(stderr, "Failed to open image file.\n");
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
};
    
BENCHMARK_DEFINE_F(IFSFixture, create_raster_test)(benchmark::State& state)
{
    while (state.KeepRunning()) {
        raster = create_raster_from_png(imgfile);
    }
}

BENCHMARK_REGISTER_F(IFSFixture, create_raster_test)
    ->Unit(::benchmark::kMicrosecond);

BENCHMARK_MAIN();
