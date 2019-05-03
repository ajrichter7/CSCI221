
#pragma once
#include "chromosome.hh"

class ClimbChromosome : public Chromosome {
 public:
 	ClimbChromosome(const ClimbChromosome&) = delete;
  	ClimbChromosome(ClimbChromosome&&) = delete;
  	ClimbChromosome& operator=(const ClimbChromosome&) = delete;
  	ClimbChromosome& operator=(ClimbChromosome&&) = delete;

 	ClimbChromosome(const Cities* cities_ptr);

 	virtual ~ClimbChromosome() = default;


 	virtual void mutate() override;

 	virtual ClimbChromosome* clone() const override;
};
