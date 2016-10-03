<?hh // strict
namespace CodeCampExport\Filters;

use Plenty\Modules\DataExchange\Contracts\Filters;
use Plenty\Modules\DataExchange\Models\FormatSetting;

class AwesomeMarketplaceFilters extends Filters
{    
    /**
     * Generate filters.
     * @param  array<FormatSetting> $formatSettings = []
     * @return array
     */
    public function generateFilters(array<FormatSetting> $formatSettings = []):array<string, mixed>
    {        
		$searchFilter = [
			'variationBase.isActive?' => [],
		];

		return $searchFilter;
    }
}
